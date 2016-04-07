close all, clear all, clc
%% 1

% Collect data
load('./Datafiles/wsA_position_level1.mat');
x = wsA_position_level1.X(:,1);
y1 = wsA_position_level1.Y(:,1);
y2 = wsA_position_level1.Y(:,2);

% Plotting
figure
plot(x.Data,y1.Data,x.Data,y2.Data)
legend('Reference','Motor')
title('C')
ylabel('Velocity')
xlabel('Time')
%% 3

% Collect data
load('./Datafiles/wsA_position_level1_long_sampling.mat');
x = wsA_position_level1_long_sampli.X(:,1);
y1 = wsA_position_level1_long_sampli.Y(:,1);
y2 = wsA_position_level1_long_sampli.Y(:,2);

% Plotting
figure
plot(x.Data,y1.Data,x.Data,y2.Data)
legend('Reference','Motor')
title('Position Response')
ylabel('Position')
xlabel('Time')
%% 3

% Collect data
load('./Datafiles/wsA_position_level1_long_sampling_voltage');
x = wsA_position_level1_long_sampli.X(:,1);
y1 = wsA_position_level1_long_sampli.Y(:,1);

% Plotting
figure
plot(x.Data,y1.Data)
title('Voltage response')
ylabel('Voltage')
xlabel('Time')
