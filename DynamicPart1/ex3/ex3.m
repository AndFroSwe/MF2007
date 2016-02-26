close all, clear all, clc
k=8; %N/m
m = 0.1; %kg
d = 0.5; %Ns/m
v = 0;
s = tf('s');
G1 = 1/((m/k)*s^2+(d/k)*s + 1);
G2 = 1/(s*m+d);
G3 = G2/G1;
transferfunctions = {G1 G2 G3};
% for i = 1:length(transferfunctions)
%     G = transferfunctions{i};
%     if(i ~= 3)
%         sim('ex3_sim')
%         figure
%         plot(result.Time,result.Data)
%         title(['Ex3: Simulink Step response G',num2str(i)])
%         print(['ex3_simulink_step_response_G',num2str(i)],'-dpng')
%     end
%     figure
%     bode(G)
%     title(['Ex3: Simulink Bode for G',num2str(i)])
%     print(['ex3_simulink_bode_G',num2str(i)],'-dpng')
%     figure
%     pzplot(G)
%     title(['Ex3: Simulink Pole-Zero Map for G',num2str(i)])
%     print(['ex3_simulink_pzmap_G',num2str(i)],'-dpng')
% end


G = transferfunctions{2};
resonance = damp(G)
freq = resonance*0.8
sim('ex3_sim')
figure
plot(G2_velocity.Time,G2_velocity.Data)
hold on
plot(appliedforce.Time,appliedforce.Data)
title(['Ex3: Simulink below resonance G2'])
print(['ex3_simulink_below_resonance_G2'],'-dpng')
freq = resonance

sim('ex3_sim')
figure
plot(G2_velocity.Time,G2_velocity.Data)
hold on
plot(appliedforce.Time,appliedforce.Data)
title(['Ex3: Simulink same as resonance G2'])
print(['ex3_simulink_same_resonance_G2'],'-dpng')
freq = resonance*1.2

sim('ex3_sim')
figure
plot(G2_velocity.Time,G2_velocity.Data)
hold on
plot(appliedforce.Time,appliedforce.Data)
title(['Ex3: Simulink over resonance G2'])
print(['ex3_simulink_over_resonance_G2'],'-dpng')


