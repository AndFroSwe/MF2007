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

%% part 4: Quantizing
% Set parameters
enable_sin = 0;     % Set 1 to enable sine input
zoh_sample_time = 1;   % Sample time in zoh [ms]
pulses_per_rev = 512;   % Pulses per revolution [-]
    

% Calculated parameters
enable_karnop = 0;  % Dont use karnop
sim_quantization_interval = 2*pi/pulses_per_rev;    % Ppr to degrees
sim_zoh_sample_time = zoh_sample_time*1e-3;  % Sample time, from ms to s

% Simulate
simtime = 1; % Sim for 1 s
sim('ex2_sim.slx')
% Plot of unquantized signal
figure
plot(sim_ex2_v_w.Time, sim_ex2_v_w.Data)
hold on
stairs(sim_ex2_v_w_sampled.Time, sim_ex2_v_w_sampled.Data, 'r')
grid on
title('Motor control with and without quantization')
xlabel('Time [s]')
ylabel('\omega [rad/s]')
legend('Unquantized velocity', 'Quantized velocity')
