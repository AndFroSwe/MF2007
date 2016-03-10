close all, clear all, clc
warning('off', 'all')
%% Load parameters
load('motor_parameters.mat)
%% Velocity Control, no inductance
motor = motor_pars;
J = J1+J2;
Jtot = motor.J + J/n^2; % Total inertia including load inertia after gear

% Transfer function of system, without control
s = tf('s');
G_nom = motor.k;
G_den = (s*Jtot + motor.d)*(motor.R) + motor.k^2;
G = G_nom/G_den;
disp('Transfer function of motor without inductance and inertial load with viscous friction')
G
disp('Risetime of the open system with no control')
G_stepinfo = stepinfo(G);
G_stepinfo.RiseTime

%% P-control
P = 1; % OBS! This value is chosen from the command rlocfind, explained below
r0 = 0;
I = 0;
D = 0;
% Plot root locus
figure
rlocus(G)
grid on
% OBS
% First run rlocus(G), then
% run command "P = rlocfind(G) to find desired P value in plot
% OBS
% Closed loop system
F_P = P;

Gc_P = minreal(F_P*G/(1 + F_P*G));
Gc_P_stepinfo = stepinfo(Gc_P);
disp('Closed loop system')
Gc_P
disp('Risetime of closed loop system')
Gc_P_stepinfo.RiseTime
fprintf('Closed loop is %0.2f times faster than open loop\n', (Gc_P_stepinfo.RiseTime/G_stepinfo.RiseTime)^-1)
disp('With pole in')
p1 = pole(Gc_P)
figure
step(Gc_P);
hold on
grid on
title(sprintf('Step response for closed loop system with K_p=%0.2f', P))


% Get phase margin
[Gm,Pm,Wgm,Wpm] = margin(Gc_P);
fprintf('Phase margin is %0.3f\n', Pm)

% Simulation parameters
% Controller polynomials. This is a regular P controller with error
% feedback
T = P;
S = P; 
R = 1;

simtime = 20;
enable_sin = 1;
sim_sin_amp = 20;
sim_sin_freq = 0.2;
I = 0;
D = 0;
% Run simulation
sim('motor_velocity.slx')
figure
plot(sim_reference)
hold on 
grid on
plot(sim_output)
title('Closed loop controller for DC motor, output velocity')
legend('Reference', 'Ouput')
xlabel('Time [s]')
ylabel('\omega [rad/s]')

%% Designing a PI controller
% PI controller, placing double poles in same position as in P controller
% Solved on paper beforehand
omega = abs(p1);
zeta = 0.7;
P = (2*Jtot*motor.R*omega*zeta - motor.k^2 - motor.d*motor.R)/motor.k;
I = (Jtot*motor.R*omega^2)/motor.k;


F_PI = P + (1/s)*I;
Gc_PI = minreal(F_PI*G/(1 + F_PI*G));
disp('Transfer function of closed system with PI controller is')
Gc_PI
disp('With poles in')
pole(Gc_PI)
[Gm,Pm,Wgm,Wpm] = margin(Gc_P);
fprintf('Phase margin is %0.3f\n', Pm)
fprintf('with DC gain %0.3f\n', dcgain(Gc_PI))

% Simulate again
% Controller parameters
S = [P I];  % = Ps + I
T = [P I];
R = [1 0];    % = s

enable_sin = 0;
simtime = 0.5;
sim('motor_velocity_2dof.slx')
figure
plot(sim_reference)
hold on 
grid on
plot(sim_output)
title('Error feedback: Closed loop PI controller for DC motor, output velocity')
legend('Reference', 'Output')
xlabel('Time [s]')
ylabel('\omega [rad/s]')

%% Output feedback
% redifine parameters
k = motor.k;
r = motor.R;
d = motor.d

% Set desired poles
omega1 =500;
omega2 = 600;
Am = [1 omega1]
A0 = s + omega2

Fo_PI = P + (1/s)*I;
Gco_PI = minreal(Fo_PI*G/(1 + Fo_PI*G));

% Calculate parameters
P =(Jtot*omega1*r+Jtot*omega2*r-d*r-k^2)/k;
I = omega1*omega2*J*r/k;

% Output feedback parameters
S = [P I];  % = Ps + I
R = [1 0];    % = s

% DC gain in B/Am
disp('DC gain is')
t0inverse = dcgain(tf(G.num{1}/G.den{1}(1), Am))
t0 = t0inverse^-1
% Define T
T =29* A0.num{1} %t0*A0.num{1}

enable_sin = 0;
simtime = 5;
sim('motor_velocity_2dof.slx')
figure
plot(sim_reference)
hold on 
grid on
plot(sim_output)
title('Output feedback: Closed loop PI controller for DC motor, output velocity')
legend('Reference', 'Output')
xlabel('Time [s]')
ylabel('\omega [rad/s]')

%% Discrete time controller
% Set parameters
enable_sin = 0;     % Set 1 to enable sine input
zoh_sample_time = 0.002;   % Sample time in zoh [ms]
pulses_per_rev = 1000;   % Pulses per revolution [-]
sim_zoh = 0.02;    

% Calculated parameters
enable_karnop = 0;  % Dont use karnop
sim_quantization_interval = 2*pi/pulses_per_rev;    % Ppr to degrees
sim_zoh_sample_time = zoh_sample_time*1e-3;  % Sample time, from ms to s
G_d = c2d(G,0.002,'zoh');
F_d = c2d(F_PI,0.002,'tustin');
Gc_d =minreal( G_d*F_d/(1+G_d*F_d));

figure
pzmap(Gc_d)


%% Position Control






