close all, clear all, clc
k=8; %N/m
m = 0.1; %kg
d = 0.5; %Ns/m
v = 0;


s = tf('s');

G = s/(m*s^2+d*s+k);

A = [ 0 1
     -k/m -d/m];
B = [0;1/m];
C = [1 0; 0 1];
D = [0;0];
sys = ss(A,B,C,D);

figure
bode(sys)
figure
step(sys)
figure
pzmap(sys)
legend('Pos')
figure
pzmap(G)
legend('Speed')
damp(sys)
resonance = damp(sys);
dcgain(sys)

%below resonance
freq = resonance*0.8;
sim('ex2_sim')
figure
plot(force.Time, force.Data,'b')
hold on
plot(speed.Time, speed.Data,'r')
title('Below Resonance')
% resonance
freq = resonance;
sim('ex2_sim')
figure
plot(force.Time, force.Data)
hold on
plot(speed.Time, speed.Data)
title('same as Resonance')
%over resonance
freq = resonance*1.2;
sim('ex2_sim')
figure
plot(force.Time, force.Data)
hold on
plot(speed.Time, speed.Data)
title('Over Resonance')


