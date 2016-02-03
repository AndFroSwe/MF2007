close all, clear all, clc
k=8; %N/m
m = 0.1; %kg
d = 0.5; %Ns/m
v = 0;


s = tf('s');

G = 1/(m*s^2+d*s+k);

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
freq = resonance*0.5;
sim('ex2_sim')
figure
plot(force.Time, force.Data,'b')
hold on
plot(speed.Time, speed.Data,'r')
title('Ex2: Simulink below Resonance')
% print('plot_ex2_simulink_below','-dpng')
sim('ex2_simscape')
figure
plot(force_simscape.Time,force_simscape.Data,'b')
hold on
plot(velocity_simscape.Time,velocity_simscape.Data,'r')
legend('Force','Speed')
title('Ex2: Simscape below Resonance')
% print('plot_ex2_simscape_below','-dpng')
% resonance
freq = resonance;
sim('ex2_sim')
figure
plot(force.Time, force.Data)
hold on
plot(speed.Time, speed.Data)
title('Ex2: Simulink Same as Resonance')
% print('plot_ex2_simulink_same','-dpng')
sim('ex2_simscape')
figure
plot(force_simscape.Time,force_simscape.Data,'b')
hold on
plot(velocity_simscape.Time,velocity_simscape.Data,'r')
legend('Force','Speed')
title('Ex2: Simscape Same as Resonance')
% print('plot_ex2_simscape_same','-dpng')
%over resonance
freq = resonance*1.5;
sim('ex2_sim')
figure
plot(force.Time, force.Data)
hold on
plot(speed.Time, speed.Data)
title('Over Resonance')
title('Ex2: Simulink over Resonance')
% print('plot_ex2_simulink_over','-dpng')
sim('ex2_simscape')
figure
plot(force_simscape.Time,force_simscape.Data,'b')
hold on
plot(velocity_simscape.Time,velocity_simscape.Data,'r')
legend('Force','Speed')
title('Ex2: Simscape over Resonance')
% print('plot_ex2_simscape_over','-dpng')


