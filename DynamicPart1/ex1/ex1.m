close all, clear all, clc
m = 0.1; %kg
d = 0.5; %Ns/m
v = 0;

s = tf('s');

Gx = 1/(m*s^2 +d*s);
Gv = 1/(m*s + d);


A = [ 0 1
      0 d/m];
B = [0 1/m];
C = [1 0;0 1];

figure
bode(Gx)
figure
bode(Gv)
figure
step(Gx)
figure
pzmap(Gx)
damp(Gx)
damp(Gv)
dcgain(Gx)
figure
dcgain(Gv)
freq = 1;
sim('ex1_sim')
figure
plot(force.Time, force.Data)
hold on
plot(speed.Time, speed.Data)
legend('Force','Speed')
title('Ex1: Simulink step')
print('plot_ex1_simulink_step','-dpng')
 sim('ex1_simscape')
 figure
 plot(force_simscape.Time,force_simscape.Data,'b')
 hold on
 plot(velocity_simscape.Time,velocity_simscape.Data,'r')
 legend('Force','Speed')
 title('Ex1: Simscape step')
 print('plot_ex1_simscape_step','-dpng')