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


%% Ex 3 With Karnopp model for friction
motor_L = motor_pars;
J = J1+J2;

%For step inputs
sim_step_v = 2.38;
% For sine inputs
sim_sin_amp = 10;
sim_sin_freq = 1;
enable_sin = 1;
% With Karnopp
F_c = 0.001;
d_v = 10;
enable_karnop = 1;

% Create atomatic string for title
if enable_sin
    title_string = sprintf('Sine input with f=%0.1f rad/s and A=%0.1f V with Karnopp',...
        sim_sin_freq, sim_sin_amp);
else
    title_string = sprintf('Step input with A=%0.1f V with Karnopp',...
        sim_step_v);
end

% simtime = 0.5;
% %Step with 1V
% sim_step_v = 1;
% enable_sin = 0;
% sim('ex3_sim.slx')
% figure
% plot(sim_ex3_v_w.Time,sim_ex3_v_w.Data);
% title('Step input with A=1 V with Karnopp')
% 
% %Step with 10V
% sim_step_v=10;
% sim('ex3_sim.slx')
% figure
% plot(sim_ex3_v_w.Time,sim_ex3_v_w.Data);
% title('Step input with A=10 V with Karnopp')

enable_sin = 1;
sim_sin_amp = 2;
sim_sin_freq = 2;
simtime = 6;
sim('ex3_sim.slx')
figure
% Plot resulting velocity
plot(sim_ex3_v_w.Time, sim_ex3_v_w.Data);
title('Sin input amp 2, freq 1')
grid on

simtime = 6;
sim_sin_amp = 5;
sim('ex3_sim.slx')
figure
plot(sim_ex3_v_trq)
hold on
plot(sim_ex3_v_clb)
legend('Torque', 'Friction')

