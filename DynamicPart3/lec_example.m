close all, clear all, clc
%% Example from lecture with Lei
%% Define parameters
J = 0.1;
k = 3.6;
d = 0.45;

%% Create model
Gp = tf([k],[J d 0])

step(Gp)

% Calculate parameters
omega = 10;
Zeta = 0.9;
omega2  = 10;

r0 = (2*J*Zeta*omega+J*omega2-d)/J
s0 = omega^2*omega2*J/k
s1 = (2*J^2*Zeta*omega*omega2+J^2*omega^2-2*J*Zeta*d*omega-J*d*omega2+d^2)/(J*k)