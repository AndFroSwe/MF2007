close all, clear all, clc
Ts = 0.002;
% TODO: PID controller
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

% motor_pars.d = 8e-6; %Viscous friction in brushes
% motor_pars.J = 10e-6;  % Rotor inertia
% % J1 = 3e-5; %Load inertia 1
% J2 = 3e-5; %Load inertia 2




%% 1: Parameter identification

% Estimated parameters
J1 = 0.00075;  % Load inertia (separated from motor inertia
motor.d = 3e-5; % Measured at amplitude 10

%% 2: parameter identification, with karnop
% Start with high speed, 24 v,  and estimating d. Fc has lower effect there.
% Then go down to 5 v and find Fc lower and upper.
J1 = 0.0006;  % Load inertia (separated from motor inertia
motor.d = 1.5e-5; % Measured at amplitude 10
F_c_upper = 1.5e-3; % Upper static friction limit
F_c_lower = 0.5e-3; % Lower static friction limit


