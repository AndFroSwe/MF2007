clear all, close all; clc;
%% Define parameters
n = 5; %Gearbox ratio
J1 = 1.8e-5; %Load inertia 1
J2 = 1.8e-5; %Load inertia 2
Vmax = 24; %Supply voltage
Vmin = -24; %Supply voltage
Imax = 430e-3; %Maximum current
sim_V = Vmax;

% Motor parameters
R = 112; % Terminal resistance [Ohm]
L = 11.4e-3;    % Terminal inductance [H]
dm = 3.8e-6; %Viscous friction in brushes
kt = 69.7e-3;    % Torque constant [Nm/A]
J_m = 7.46e-7;  % Rotor inertia
kemf = 60/(2*pi*137);

s = tf('s');

Gm = 0.0697/(0.0002448*s+0.005284)

%% TASK 5

kf = 0.05; %[Nm/rad]
df = 0.0001; %[Nms/rad]

A = [zeros(2) eye(2);-[kf/J1 -kf/J1;-kf/J2 kf/J2] -[df/J1 -df/J1;-df/J2 df/J2]];
B = [0 0 J_m/J1 0]';
C = [0 0 1 0];

C2 = [0 0 0 1];



[num, den] = ss2tf(A, B, C, 0, 1);
[num2, den2] = ss2tf(A, B, C2, 0, 1);

Gs=tf(num, den); 
Gs2 = tf(num2, den2);

s = tf('s');

Gtot = tf(Gs * s * Gm); % Transfer for load velocity
Gtot2 = tf(Gs2 * s * Gm); % Transfer for motor velocity

%1
[A2, B2, C2, D2] = tf2ss(Gtot.num{1},Gtot.den{1});

%2
figure
subplot(2,1,1)
pzmap(Gtot)
title('Pzmap for the Load velocity model')
% figure
subplot(2,1,2)
pzmap(Gtot2)
title('Pzmap for the Motor velocity model')
%3
figure
subplot(2,1,1)
step(Gtot) %Load
title('Step response for the Load velocity model')
% figure
subplot(2,1,2)
step(Gtot2) %Motor
title('Step response for the Motor velocity model')
figure
subplot(2,1,1)
bode(Gtot)
title('Bode plot for the Load velocity model')
% figure
subplot(2,1,2)
bode(Gtot2)
title('Bode plot for the Motor velocity model')

%4
%See above







