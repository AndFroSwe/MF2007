close all, clear all, clc
warning('off', 'all')
%% Discrete controller
% Load parameters
load('motor_parameters.mat')
m = motor_pars;
%% Discrete time controller

disp('Open system')
% System parameters
Go = tf([m.k/(m.R*Jtot)], [1 (m.d/Jtot + m.k^2/(m.R*Jtot))]);
Go = Go*1/n % Add this to get gear box in model

    % Set parameters
    enable_sin = 0;             % Set 1 to enable sine input
    zoh_sample_time = 0.002;    % Sample time in zoh [ms]
    pulses_per_rev = 1000;      % Pulses per revolution [-]
    sim_zoh = 0.02;    

    % Calculated parameters
    enable_karnop = 0;  % Dont use karnop
    sim_quantization_interval = 2*pi/pulses_per_rev;    % Ppr to degrees
    sim_zoh_sample_time = zoh_sample_time*1e-3;  % Sample time, from ms to s
    G_d = c2d(G,0.002,'zoh');
    F_d = c2d(F_PI,0.002,'tustin');
    Gc_d = minreal( G_d*F_d/(1+G_d*F_d));

    figure
    pzmap(Gc_d)
