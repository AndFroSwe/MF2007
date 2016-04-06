close all, clear all, clc
% MOTOR 4
warning('off', 'all')
s = tf('s');
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
%% Parameter identification
% Estimated parameters
J1 = 0.00006;  % Load inertia (separated from motor inertia
motor.d = 1.35e-5; % Measured at amplitude 24
% Model parameters
pulses_per_rev = 1000; % Defined on motor
quant = 2*pi/pulses_per_rev;    % Ppr to degrees

%% parameter identification, with karnop
% Start with high speed, 24 v,  and estimating d. Fc has lower effect there.
% Then go down to 5 v and find Fc lower and upper.
 J1 = 0.0006;  % Load inertia (separated from motor inertia
 motor.d = 1e-5; % Measured at amplitude 24
 F_c_upper = 1.5e-3; % Upper static friction limit
 F_c_lower = 1.5e-3; % Lower static friction limit
 F_c = 1.5e-3;

%%  Controlling the motor
%  Velocity Controller
Jtot = motor.J + J1/n^2;
disp('Open loop system')

% Transfer of motor without indctance
Go = tf([motor.k/(motor.R*Jtot)], [1 (motor.d/Jtot + motor.k^2/(motor.R*Jtot))])/s
a = Go.num{1}(3);
b = Go.den{1}(2);
B = tf([0 0 a], [0 0 1])
A = tf([1 b 0], [0 0 1])



% design continuous controller
% Am
omega1 = 14;
omega2 = 14;
Am = (s + omega1)*(s + omega2);

% Ao
omega3 = 35;
Zeta = 1;
Ao = s^2 + 2*Zeta*omega3*s + omega3^2;



% feedback parameters
r0 =2*Zeta*omega3-b+omega1+omega2
s0 = omega1*omega2*omega3^2/a
s1 = omega3*(2*Zeta*omega1*omega2+omega1*omega3+omega2*omega3)/a
s2 = (-2*Zeta*b*omega3+2*Zeta*omega1*omega3+2*Zeta*omega2*omega3+b^2-b*omega1-b*omega2+omega1*omega2+omega3^2)/a
S = tf([s2 s1 s0], [0 0 1])
R = tf([1 r0 0], [0 0 1])

Gfb = S/R

% feed forward parameters
t0 = dcgain(B/Am)^-1
T = t0*Ao

Gff = T/R

% closed loop system
Gc = B*T/(A*R + B*S)
pole(Gc)

%% discrete controller
% calculate sampling time
wb = 35, % fastest pole
ws = wb*10;
Ts = 2*pi/ws

% discretize controllers
Gff_d = c2d(T/R, Ts, 'tustin')
Gfb_d = c2d(S/R, Ts, 'tustin')










