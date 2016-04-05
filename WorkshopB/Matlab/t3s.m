close all, clear all, clc
% MOTOR 4
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
enable_sin = 1;
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

motor = motor_pars;
Ts = 0.002

%% 1: Parameter identification

% Estimated parameters
J1 = 0.00006;  % Load inertia (separated from motor inertia
motor.d = 1.35e-5; % Measured at amplitude 24

%% 2: parameter identification, with karnop
% Start with high speed, 24 v,  and estimating d. Fc has lower effect there.
% Then go down to 5 v and find Fc lower and upper.
 J1 = 0.0006;  % Load inertia (separated from motor inertia
 motor.d = 1e-5; % Measured at amplitude 24
 F_c_upper = 1.5e-3; % Upper static friction limit
 F_c_lower = 1.5e-3; % Lower static friction limit
 F_c = 1.5e-3;

%% 4: Controlling the motor
%% 4.1: Velocity Controller
Jtot = motor.J + J1/n^2;
disp('Open loop system')

% Transfer of motor without indctance
Go = tf([motor.k/(motor.R*Jtot)], [1 (motor.d/Jtot + motor.k^2/(motor.R*Jtot))])

% Parameters for Maple
a = Go.num{1}(2)
b = Go.den{1}(2)

% Error feedback
% Place poles
omega1 = 10;
omega2 = 5;

% Calculate regulator parameters
s1 = -(b-omega1-omega2)/a; % P 
s2 = omega1*omega2/a; % I

% Controller parameters, PI controller
S_vector = [s1 s2];
R_vector = [1 0];

% Controller tf
F = tf(S_vector, R_vector);
disp('Error feedback closed loop')
Gc_error = minreal(F*Go/(1 + F*Go))
figure
pzmap(Gc_error)
grid on
title('PZ map for error feedback system')

% Output feedback
% Calculate T
t0 = dcgain(tf(Go.num{1}, [1 omega1]))^-1;
T_vector = t0*[1 omega2];

A = tf(Go.den{1}, [1]);
B = tf(Go.num{1}, [1]);
T = tf(T_vector, [1]);
R = tf(R_vector, [1]);
S = tf(S_vector, [1]);
Gc_output = minreal((B*T)/(A*R + B*S))
figure
pzmap(Gc_output)
title('Output feedback pole zero map')
grid on


%% Sensitivity
c = 0.5107;
d = 1.988;

s=tf('s');
Am = s+omega1;
Ao = s+omega2;
Go = B/A;

Se = (A*R)/(Am*Ao)
Te = (B*S)/(Am*Ao)

bode(Se)
hold on
bode(Te)

title('Sensitivity functions')
legend('Se', 'Te');


