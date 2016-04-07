close all, clear all, clc
%% 1

% Collect data
load('./Datafiles/VelocityController/sin_amp10_freq02.mat');
x = sin_amp10_freq02.X(:,1);
y1 = sin_amp10_freq02.Y(:,3);
y2 = sin_amp10_freq02.Y(:,2);

% Plotting
figure
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('Sine Wave amp: 10V, freq: 0.2Hz')
ylabel('Velocity')
xlabel('Time')

%%2
% Collect data
load('./Datafiles/VelocityController/sin_amp10_freq02_HOLD.mat');
x = sin_amp10_freq02_HOLD.X(:,1);
y1 = sin_amp10_freq02_HOLD.Y(:,3);
y2 = sin_amp10_freq02_HOLD.Y(:,2);

% Plotting
figure
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('Sine Wave amp: 5V, freq: 0.2Hz with load torque')
ylabel('Velocity')
xlabel('Time')
%% 3

% Collect data
load('./Datafiles/VelocityController/sq_amp50_freq05.mat');
x = sq_amp50_freq016.X(:,1);
y1 = sq_amp50_freq016.Y(:,1);
y2 = sq_amp50_freq016.Y(:,2);

% Plotting
figure
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('Square Wave amp: 50V, freq: 0.5Hz')
ylabel('Velocity')
xlabel('Time')

%%4
% Collect data
load('./Datafiles/VelocityController/volt_amp50_freq05.mat');
x = volt_amp50_freq05.X(:,1);
y1 = volt_amp50_freq05.Y(:,1);

% Plotting
figure
plot(x.Data,y1.Data)
title('Voltage response for sine wave amp: 50V, freq: 0.5Hz')
ylabel('Voltage')
xlabel('Time')
%% 5

% Collect data
load('./Datafiles/VelocityController/volt_sin_amp10_freq02.mat');
x = volt_sin_amp10_freq02.X(:,1);
y1 = volt_sin_amp10_freq02.Y(:,1);

% Plotting
figure
plot(x.Data,y1.Data)
legend('Voltage')
title('Voltage response for sine wave amp: 10V, freq: 0.2Hz')
ylabel('Voltage')
xlabel('Time')

%%6
% Collect data
load('./Datafiles/VelocityController/volt_sin_amp10_freq02_HOLD.mat');
x = volt_sin_amp10_freq02_HOLD.X(:,1);
y1 = volt_sin_amp10_freq02_HOLD.Y(:,1);

% Plotting
figure
plot(x.Data,y1.Data)
legend('Voltage')
title('Voltage response for sine wave amp: 10V, freq: 0.2Hz with load torque')
ylabel('Velocity')
xlabel('Time')