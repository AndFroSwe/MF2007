clear all, close all;
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

% Motor model
A = [-R/L  -kt*n/L;
    kt/J_m    dm*n/J_m];
B = [sim_V/L;
    0];
C = [0 1];
D = [0];

[mnum, mden] = ss2tf(A, B, C, D);

Gm = tf(mnum, mden);

%% TASK 5

kf = 0.05; %[Nm/rad]
df = 0.0001; %[Nms/rad]

A = [zeros(2) eye(2);-[kf/J1 -kf/J1;-kf/J2 kf/J2] -[df/J1 -df/J1;-df/J2 df/J2]];
B = [0 0 J_m/J1 0]';
C = [0 0 1 0];



[num, den] = ss2tf(A, B, C, 0, 1);

Gs=tf(num, den);

s = tf('s');

Gs = minreal(Gs);

Gtot = tf(Gs * s * Gm)

%Gtot = minreal(Gtot);

figure(1)
bode(Gtot)
% figure(2)
% pzmap(Gtot)
figure(3)
step(Gm)
figure(4)
step(Gtot)
figure(5)
step(Gs)







