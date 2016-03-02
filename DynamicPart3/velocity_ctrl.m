close all, clear all, clc
warning('off', 'all')
%% Define parameters
n = 5; %Gearbox ratio
J1 = 1.8e-5; %Load inertia 1
J2 = 1.8e-5; %Load inertia 2
Vmax = 24; %Supply voltage
Vmin = -24; %Supply voltage
Imax = 430e-3; %Maximum current
V_i = Vmax;
V_w = Vmax;
sim_v = Vmax;
% Set up generic simulation parameters, change when using sine input or
% karnop
F_c = 1e-3;
d_v = 1;
enable_sin = 0;
enable_karnop = 1;
sim_sin_amp = 1;
sim_sin_freq = 1;
sim_quantization_interval = 0;
sim_zoh_sample_time = 0;
% Motor parameters
motor_pars = struct(); % Create empty struct for motor
motor_pars.R = 112; % Terminal resistance [Ohm]
motor_pars.L = 11.4e-3;    % Terminal inductance [H]
motor_pars.d = 3.8e-6; %Viscous friction in brushes
motor_pars.k = 69.7e-3;    % Torque constant [Nm/A]
motor_pars.J = 7.46e-7;  % Rotor inertia

%% Velocity Control, no inductance
motor = motor_pars;
J = J1+J2;
Jtot = motor.J + J/n^2; % Total inertia including load inertia after gear

% Transfer function of system, without control
s = tf('s');
G_nom = motor.k;
G_den = (s*Jtot + motor.d)*(motor.R) + motor.k;
G = G_nom/G_den;
disp('Transfer function of motor without inductance and inertial load with viscous friction')
G
disp('Risetime of the open system with no control')
G_stepinfo = stepinfo(G);
G_stepinfo.RiseTime

%% P-control
P = 3; % OBS! This value is chosen from the command rlocfind, explained below
% Plot root locus
figure
rlocus(G)
grid on
% OBS
% First run rlocus(G), then
% run command "P = rlocfind(G) to find desired P value in plot
% OBS
% Closed loop system
F_P= P;

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

simtime = 10;
enable_sin = 1;
sim_sin_amp = 200;
sim_sin_freq = 10;
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
zeta = 1;
P = (2*motor.J*motor.R*omega*zeta - motor.k - motor.d*motor.R)/motor.k%-(2*p1*motor.R*Jtot + motor.k + motor.d*motor.R)/motor.k
I = (motor.J*motor.R*omega^2)/motor.k%(p1^2*Jtot*motor.R)/motor.k


F_PI = P + 1/s*I;
Gc_PI = minreal(F_PI*G);
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
sim('motor_velocity.slx')
figure
plot(sim_reference)
hold on 
grid on
plot(sim_output)
title('Closed loop PI controller for DC motor, output velocity')
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
I = 2;
G_d = c2d(G,0.002,'zoh');
F_d = c2d(F_PI,0.002,'tustin');
Gc_d =minreal( G_d*F_d/(1+G_d*F_d));

figure
pzmap(Gc_d)


%% Position Control





