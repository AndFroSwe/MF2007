% TODO: PID controller
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
r0 = 0;     % Filter coefficient in controller model
% Motor parameters
motor_pars = struct(); % Create empty struct for motor
motor_pars.R = 112; % Terminal resistance [Ohm]
motor_pars.L = 11.4e-3;    % Terminal inductance [H]
motor_pars.d = 3.8e-6; %Viscous friction in brushes
motor_pars.k = 69.7e-3;    % Torque constant [Nm/A]
motor_pars.J = 7.46e-7;  % Rotor inertia

%% Position Control, no inductance
motor = motor_pars;
J = J1+J2;
Jtot = motor.J + J/n^2; % Total inertia including load inertia after gear

% Transfer function of system, without control
s = tf('s');
G_nom = motor.k;
G_den = (s*Jtot + motor.d)*(motor.R) + motor.k;
G = G_nom/G_den*1/s;
disp('Transfer function of motor without inductance and inertial load with viscous friction')
G

%% P-control
P = 81; % OBS! This value is chosen from the command rlocfind, explained below
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
disp('With pole in')
p = pole(Gc_P)
figure
step(Gc_P);
hold on
grid on
title(sprintf('Step response for closed loop system with K_p=%0.2f', P))


% Get phase margin
[Gm,Pm,Wgm,Wpm] = margin(Gc_P);
fprintf('Phase margin is %0.3f\n', Pm)

% Simulation parameters
simtime = 10;
enable_sin = 1;
sim_sin_amp = 200;
sim_sin_freq = 10;
I = 0;
D = 0;
% Run simulation
sim('motor_position.slx')
figure
plot(sim_reference)
hold on 
grid on
plot(sim_output)
title('Closed loop P controller for DC motor, output velocity')
legend('Reference', 'Ouput')
xlabel('Time [s]')
ylabel('\omega [rad/s]')

%% Designing a PD controller
% PD controller, placing double poles in same position as in P controller
% Solved on paper beforehand
% TODO: Fix r0. Other than small r0 forces the model to be unstable.

% Because of Maple
J = motor.J;
r = motor.R;
d = motor.d;
k = motor.k;

% Regulator parameters
omega = real(abs(p(1)));
omega2 = 100
zeta = 0.9;
P = (motor.J*motor.R*omega^2*omega2)/motor.k;
I = 0;
D = (2*J^2*zeta*omega*omega2*r^2+J^2*omega^2*r^2-2*J*zeta*d*omega*r^2-2*J*zeta*k*omega*r-J*d*omega2*r^2-J*k*omega2*r+d^2*r^2+2*d*k*r+k^2)/(J*k*r)
r0 = 0;%(2*J*zeta*omega*r+J*omega2*r-d*r-k)/(J*r);

F_PD = (P + s*D)/(r0 + s);
Gc_PD = minreal(F_PD*G/(1+F_PD*G));
disp('Transfer function of closed system with PI controller is')
Gc_PD
disp('With poles in')
pole(Gc_PD)
[Gm,Pm,Wgm,Wpm] = margin(Gc_PD);
fprintf('Phase margin is %0.3f\n', Pm)
fprintf('with DC gain %0.3f\n', dcgain(Gc_PD))

% Simulate again
% Controller parameters
enable_sin = 0;
simtime = 0.5;
sim('motor_position.slx')
figure
plot(sim_reference)
hold on 
grid on
plot(sim_output)
title('Closed loop PD controller for DC motor, output position')
legend('Reference', 'Output')
xlabel('Time [s]')
ylabel('\phi [rad]')

%% PID controller

omega = real(abs(p(1)));
omega2 = 100;

% Because of Maple
J = motor.J;
r = motor.R;
d = motor.d;
k = motor.k;

% Parameters from Maple "PIDcontroller.mw"
P = abs(J^2*omega*r^2*(2*zeta*omega2+omega)/(k*(J*r-d*r-k)));
I = abs(omega^2*omega2*J^2*r^2/((J*r-d*r-k)*k));
D = abs((2*J^2*zeta*omega*r^2+J^2*omega2*r^2-J*d*r^2+d^2*r^2-J*k*r+2*d*k*r+k^2)/(k*(J*r-d*r-k)));
r0 = abs(J*r/(J*r-d*r-k));

% Find the PID controller and the closed loop system tf
F_PID = (D*s^2+P*s+I)/(s*(r0*s+1));
% Closed loop system
Gc_PID = minreal(F_PID*G/(1 + F_PID*G));
disp('Transfer function of closed system with PI controller is')
Gc_PID
disp('With poles in')
pole(Gc_PID)
[Gm,Pm,Wgm,Wpm] = margin(Gc_PID);
fprintf('Phase margin is %0.3f\n', Pm)
fprintf('with DC gain %0.3f\n', dcgain(Gc_PID))

% Simulation 
% Simulate again
% Controller parameters
enable_sin = 0;
simtime = 100;
sim('motor_position.slx')
figure
plot(sim_reference)
hold on 
grid on
plot(sim_output)
title('Closed loop PID controller for DC motor, output position')
legend('Reference', 'Output')
xlabel('Time [s]')
ylabel('\phi [rad]')

%% Discrete time controller
% Set parameters
enable_sin = 0;     % Set 1 to enable sine input
zoh_sample_time = 0.01;   % Sample time in zoh [ms]
pulses_per_rev = 1000;   % Pulses per revolution [-]
sim_zoh = 0.01;    

% Calculated parameters
enable_karnop = 0;  % Dont use karnop
sim_quantization_interval = 2*pi/pulses_per_rev;    % Ppr to degrees
sim_zoh_sample_time = zoh_sample_time*1e-3;  % Sample time, from ms to s
G_d = c2d(Gc_PID,sim_zoh,'zoh');
F_d = c2d(F_PID,sim_zoh,'tustin');
Gc_d =minreal( G_d*F_d/(1+G_d*F_d));

figure
pzmap(Gc_d)

%% Hydraulic cylinder
% Velocity controller for hydraulic system
% TODO: Verify that model works in both directions
% TODO: Design position controller in outer loop (cascaded)
% TODO: Make discrete time approximation
% TODO: Find longest sampling time

% Piston parameters
Dc = 0.05; % Cylinder diameter m
Dp = 0.02; %Piston rod diameter m
lp = 0.7; %maximum piston stroke m
m = 100; % total moving mass kg
uf = 200; %Linear friction coeff Ns/m
Rv = 1e-4; % Flow constant
xv = 0.01; %Valve opening -1 - 1 cm;
Ps = 20e6; %Supply pressure MPA
Pt = 0 ; %Tank return pressure MPA
poil = 1000; % Oil density kg/m^3
Tforce = 1;
B = 2e9; %Bulk modulus
A1 = (Dc/2)^2*pi; %Area of piston
A2 = (Dc/2)^2*pi - (Dp/2)^2*pi;

Volume0 = A1*lp;
Cf = Volume0/B; %Compressibility Oil

%Linearization 
Am = (A1+A2)/2;

Fe = 0; % External force N
df = uf; % Friction
syms v p1 p2

% Case if positive piston speed
if xv >= 0
    eq1 = (1/m)*(Am*(p1-p2)-Fe-df*v )==0;
    eq2 = (1/Cf)*(Rv*sqrt(Ps-p1)*xv-Am*v )==0;
    eq3 = (1/Cf)*(Am*v-Rv*sqrt(p2)*xv) == 0;
    % Solve for stationary points
    solution = solve([eq1,eq2,eq3],[v,p1,p2]);
    v0 = double(solution.v);
    p10 = double(solution.p1);
    p20 = double(solution.p2);
    R1 = -Rv*xv/(2*sqrt(Ps-p10)*Cf);
    R2 = -Rv*xv/(2*sqrt(p20)*Cf);
    K1 = Rv*sqrt(Ps-p10)/Cf;
    K2 = -Rv*sqrt(p20)/Cf;
end

% Case if negative piston speed
if xv < 0
    eq1 = (1/m)*(Am*(p1-p2)-Fe-df*v) == 0;
    eq2 = (1/Cf)*(Rv*sqrt(abs(p1))*xv-Am*v) == 0;
    eq3 = (1/Cf)*(Am*v-Rv*sqrt(abs(Ps-p2))*xv) == 0;
    % Solve for stationary points
    solution = solve([eq1,eq2,eq3],[v,p1,p2]);
    v0 = double(solution.v);
    p10 = double(solution.p1);
    p20 = double(solution.p2);
    R1 = Rv*xv/(2*sqrt(abs(p10))*Cf);
    R2 = Rv*xv/(Cf*sqrt(abs(Ps-p20)));
    K1 = Rv*sqrt(p10)/Cf;
    K2 = -Rv*sqrt(Ps-p20)/Cf;
end

% State space representation
A = [-df/m Am/m -Am/m;
    -Am/Cf R1 0;
    Am/Cf 0 R2];

B = [ 0 -1/m;
    K1 0;
    K2 0];

C = [1 0 0; 0 1 0; 0 0 1];
D = [0 0; 0 0; 0 0];
sys = ss(A,B,C,D);
% Create transfer function
[NUM,DEN] = ss2tf(A,B,C,D,1);
Fe = 10000;

% Run simulation model
A1 = Am;
A2 = Am;
sim('hydraulic_ex3.slx')
figure
plot(sim_p1)
hold on
grid on
plot(sim_p2)
p1lin = sim_linear.Data(:,2)+p10;
p2lin = sim_linear.Data(:,3)+p20;

plot(sim_linear.Time,p1lin)
plot(sim_linear.Time,p2lin)
legend('P1sim','P2sim','P1lin','P2lin')
figure
plot(sim_velocity)
hold on
plot(sim_linear.Time,sim_linear.Data(:,1))
legend('Velocity simulated','Velocity Linear')





