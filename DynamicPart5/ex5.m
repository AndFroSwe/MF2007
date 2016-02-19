clear all, close all, clc;
%% Define parameters
n = 5; %Gearbox ratio
J1 = 1.8e-5; %Load inertia 1
J2 = 1.8e-5; %Load inertia 2
Vmax = 24; %Supply voltage
Vmin = -24; %Supply voltage
Imax = 430e-3; %Maximum current
V_i = Vmax;
V_w = Vmax;
sim_V = Vmax;
% Motor parameters
motor_pars = struct(); % Create empty struct for motor
motor_pars.R = 112; % Terminal resistance [Ohm]
motor_pars.L = 11.4e-3;    % Terminal inductance [H]
motor_pars.d = 3.8e-6; %Viscous friction in brushes
motor_pars.k = 69.7e-3;    % Torque constant [Nm/A]
motor_pars.J_m = 7.46e-7;  % Rotor inertia

%% TASK 5

sim_V = 24; %[V]
kf = 0.05; %[Nm/rad]
df = 0.0001; %[Nms/rad]

M = diag([J1 J2]);
K = [kf -kf;-kf kf];
D = [df -df;-df df];
% Motor = [0.03 0;0 0.03];

% A = [zeros(2) eye(2);-M^-1*K -M^-1*Bd];
% B = [Motor; M^-1];
% C = [0 1 0 0];
% 
% F = [0.03*n 0; 0 0.03*n];
% 
A = [zeros(2) eye(2);[-kf/J2 kf/J2;kf/J1 -kf/J1] [-df/J2 df/J2;df/J1 -df/J1]];
B = [0 0.03/J1 0 0]';
% B = [F; M^-1];
C = [0 0 1 0];



[num, den] = ss2tf(A, B, C, 0, 1);

Gs=tf(num, den);

Gs = minreal(Gs);

bode(Gs)
figure
pzmap(Gs)
figure
step(Gs)







