close all, clear all, clc
 
R1 = 200;
R2 = 200;
C = 10e-6;
U = 12;
time = 0.25;

s = tf('s');

G1 = 1/(R1*C*s + 1);
S2 = R2/(C*R1*R2*s+R1+R2);

[A1,B1,C1,D1] = tf2ss(G1.num{1},G1.den{1});
[A2,B2,C2,D2] = tf2ss(S2.num{1},S2.den{1});


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

dcgain(G1)
dcgain(S2)

damp(G1)
damp(S2)


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