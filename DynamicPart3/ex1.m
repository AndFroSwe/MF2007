close all, clear all, clc

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

%% Velocity Control
motor = motor_pars;
J = J1+J2;
Jtot = motor.J + J/n^2; % Total inertia including load inertia after gear
% Model
%   named motor_model.slx

% Transfer function of system, without control
s = tf('s');
G_nom = motor.k;
G_den = (s*Jtot + motor.d)*(s*motor.L + motor.R) + motor.k^2;
G = G_nom/G_den;
disp('Transfer function of motor with inductance and inertial load with viscous friction')
G

% P-control
P = 20; % OBS! This value is chosen from the command rlocfind, explained below
% Plot root locus
figure
rlocus(G)
grid on
% OBS
% Run command "P = rlocfind(G) to find desired P value in plot
% OBS
% Closed loop system
F = P;
Gc = F*G/(1 + F*G);
disp('Closed loop system')
Gc
figure
step(Gc);
hold on
grid on
legend('Closed loop system', 'Open system')
title(sprintf('Step response for closed loop system with K_p=%0.2f', P))












