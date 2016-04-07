close all, clear all, clc
%% 1

% Collect data
load('./Datafiles/wsA_position_level1_long_sampling.mat');
x = wsA_position_level1_long_sampli.X(:,1);
y1 = wsA_position_level1_long_sampli.Y(:,1);
y2 = wsA_position_level1_long_sampli.Y(:,2);

% Plotting
figure
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('Sine Wave amp: 10V, freq: 0.2Hz')
ylabel('Velocity')
xlabel('Time')

