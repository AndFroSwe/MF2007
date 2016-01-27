close all, clear all, clc
m = 0.1; %kg
d = 0.5; %Ns/m
v = 0;

s = tf('s');

G = 1/(m*s^2 +d*s);

A = [ 0 1
      0 d/m];
B = [0 1/m];
C = [1 0];

figure
bode(G)
figure
step(G)
figure
pzmap(G)
damp(G)
dcgain(G)
freq = 10;
sim('ex1_sim')
figure
plot(force.Time, force.Data)
hold on
plot(speed.Time, speed.Data)
legend('Force','Speed')

 sim('ex1_simscape')
% figure
% plot(force_simscape.Time,force_simscape.Data)
% hold on
% plot(velocity_simscape.Time,velocity_simscape.Data)