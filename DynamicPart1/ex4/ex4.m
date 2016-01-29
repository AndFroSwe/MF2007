close all, clear all, clc
 
R1 = 200;
R2 = 200;
C = 10e-6;
U = 12;
time = 0.25;

s = tf('s');

G1 = 1/(R1*C*s + 1);


bode(G1)
print('ex4_S1_bode','-dpng')
figure
pzplot(G1)
print('ex4_S1_pz','-dpng')
figure
step(G1)
print('ex4_S1_step','-dpng')

sim('ex4_s1_simscape')
figure
plot(s1_voltage.Time,s1_voltage.Data)
figure



sim('ex4_s1_simulink')
figure
plot(s1_sim_voltage.Time,s1_sim_voltage.Data)
figure
figure
plot(s2_sim_voltage.Time,s2_sim_voltage.Data)

% V-R1*i - integral(1/C)*i = 0
% V = i(R1-1/C * integral(i)
% 
% x1prick = 1/R1*C  (-X1 +V)