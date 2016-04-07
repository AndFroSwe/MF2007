close all, clear all, clc
%% 1

% Collect data
load('./Datafiles/voltage_level1_position.mat');
x = voltage_level1_position.X(:,1);
y1 = voltage_level1_position.Y(:,1);

% Plotting
figure
plot(x.Data,y1.Data)
title('Voltage response from position controller')
ylabel('Voltage')
xlabel('Time')

%%2
% Collect data
load('./Datafiles/wsA_position_level1.mat');
x = wsA_position_level1.X(:,1);
y1 = wsA_position_level1.Y(:,1);
y2 = wsA_position_level1.Y(:,2);

% Plotting
figure
plot(x.Data,y1.Data,x.Data,y2.Data)
legend('Ref','Model')
title('Position response from the controller')
ylabel('Position')
xlabel('Time')
