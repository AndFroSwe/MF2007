clear all, close all, clc;
warning('off', 'all')
%% Define parameters
n = 5; %Gearbox ratio
J1 = 1.8e-5; %Load inertia 1
J2 = 1.8e-5; %Load inertia 2
Vmax = 1; %Supply voltage
Vmin = -24; %Supply voltage
Imax = 430e-3; %Maximum current
V_i = Vmax;
V_w = Vmax;
sim_V = Vmax;
% Set up generic simulation parameters, change when using sine input or
% karnop
F_c = 0.001;
d_v = 1;
enable_sin = 0;
enable_karnop = 0;
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
motor_pars.J_m = 7.46e-7;  % Rotor inertia

%% Exercise 2
J = (J1 + J2);
disp('Exercise 2')
motor_L = motor_pars;
motor_L.L = 0;

% Simulate model to get data
disp('Simulating ex2...')
simtime = 5;
sim_step_v = 1;
enable_sin = 0;
sim('ex2_sim.slx');

% Voltage control
% Transfer function
disp('Transfer function')
motor_L.tf_w = tf([motor_L.k], [(motor_L.J_m + J/n^2)*motor_L.R (motor_L.k^2 + motor_L.d*motor_L.R)]);
motor_L.tf_w

figure
step(motor_L.tf_w)
hold on
plot(sim_ex2_v_w.Time, sim_ex2_v_w.Data, 'g')
hold on
motorNoL = tf([0 0 2.797e06], [1 9826 2.12e05]);
step(motorNoL)
title('Step for voltage controlled DC motor')
legend('No inductance, tf', 'No inductance, model', 'Inductance')
figure
pzmap(motor_L.tf_w)
title('PZ map for voltage controlled DC motor with no inductance')

% % Current control
% motor_L.tf_i = tf([motor_L.k], [(motor_L.J_m + J/n^2) motor_L.d]);
% figure
% step(motor_L.tf_i)
% title('Step for DC motor with i control')
% figure
% pzmap(motor_L.tf_i)
% title('PZ map for DC motor with i control')
