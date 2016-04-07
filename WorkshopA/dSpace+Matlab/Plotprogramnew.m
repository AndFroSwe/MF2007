close all, clear all, clc
%% 1

% Collect data

load('./Datafiles/VelocityController/sin_amp10_freq02.mat');
x = sin_amp10_freq02.X(:,1);
y1 = sin_amp10_freq02.Y(:,2);
y2 = sin_amp10_freq02.Y(:,3);

% Plotting
figure
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('Sine Wave amp: 10V, freq: 0.2Hz')
ylabel('Velocity')
xlabel('Time')