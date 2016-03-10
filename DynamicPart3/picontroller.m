close all, clear all, clc
warning('off', 'all')
%% PI controller
% Load parameters
load('motor_parameters.mat')
m = motor_pars;

%% Create model function
Jtot = m.J + (J1 + J2)/n^2;

disp('Open loop system')
% Transfer of motor without indctance
Go = tf([m.k/(m.R*Jtot)], [1 (m.d/Jtot + m.k^2/(m.R*Jtot))]);
Go = Go*1/n % Add this to get gear box in model


