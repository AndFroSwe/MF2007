close all, clear all, clc
%% 

% Collect data
load('./Datafiles/sq_amp10_freq016.mat');
x = sq_amp10_freq016.X(:,1);
y1 = sq_amp10_freq016.Y(:,1);
y2 = sq_amp10_freq016.Y(:,2);

% Plotting
figure
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('Square Wave Amplitude 10')
ylabel('Velocity')
xlabel('Time')

% Collect data
load('./Datafiles/sq_amp5_freq016.mat');
x = sq_amp5_freq016.X(:,1);
y1 = sq_amp5_freq016.Y(:,1);
y2 = sq_amp5_freq016.Y(:,2);

% Plotting
figure
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('Square Wave Amplitude 5')
ylabel('Velocity')
xlabel('Time')

% Collect data
load('./Datafiles/sq_amp20_freq016.mat');
x = sq_amp20_freq016.X(:,1);
y1 = sq_amp20_freq016.Y(:,1);
y2 = sq_amp20_freq016.Y(:,2);

% Plotting
figure
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('Square Wave  Amplitude 20')
ylabel('Velocity')
xlabel('Time')
