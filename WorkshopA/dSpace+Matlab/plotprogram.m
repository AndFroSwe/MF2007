close all, clear all, clc
%% 1

% Collect data
load('./Datafiles/l2_sin_amp5_freq1.mat');
x = l2_sin_amp5_freq1.X(:,1);
y1 = l2_sin_amp5_freq1.Y(:,1);
y2 = l2_sin_amp5_freq1.Y(:,2);

% Plotting
figure
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('Sin Wave amp: 5V, freq: 1Hz')
ylabel('Velocity')
xlabel('Time')

%% 2
% Collect data
load('./Datafiles/l2_sq_amp24_freq016_d_tuned_after_fc_5amp_tuned');
x = l2_sq_amp24_freq016_d_tuned_aft.X(:,1);
y1 = l2_sq_amp24_freq016_d_tuned_aft.Y(:,1);
y2 = l2_sq_amp24_freq016_d_tuned_aft.Y(:,2);

% Plotting
figure
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('Square Wave amp: 24V, freq: 0.16Hz tuned after 5V amp')
ylabel('Velocity')
xlabel('Time')

%% 3
% Collect data
load('./Datafiles/l2_sq_amp24_freq016_fc_tuned.mat');
x = l2_sq_amp24_freq016_fc_tuned.X(:,1);
y1 = l2_sq_amp24_freq016_fc_tuned.Y(:,1);
y2 = l2_sq_amp24_freq016_fc_tuned.Y(:,2);

% Plotting
figure
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('Square Wave amp: 24V, freq: 0.16Hz, tuned')
ylabel('Velocity')
xlabel('Time')

%% 4
% Collect data
load('./Datafiles/l2_sq_amp5_freq016_fc_tuned');
x = l2_sq_amp5_freq016_fc_tuned.X(:,1);
y1 = l2_sq_amp5_freq016_fc_tuned.Y(:,1);
y2 = l2_sq_amp5_freq016_fc_tuned.Y(:,2);

% Plotting
figure
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('Square Wave amp: 5, freq: 0.16Hz, tuned')
ylabel('Velocity')
xlabel('Time')

%%LEVEL 1
%% 5
% Collect data
load('./Datafiles/sq_amp24_freq016');
x = sq_amp24_freq016.X(:,1);
y1 = sq_amp24_freq016.Y(:,1);
y2 = sq_amp24_freq016.Y(:,2);

% Plotting
figure
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('Square Wave amp: 24V, freq: 0.16Hz')
ylabel('Velocity')
xlabel('Time')

%% 6
% Collect data
load('./Datafiles/sq_amp24_freq016_d_J_tuned.mat');
x = sq_amp24_freq016_d_J_tuned.X(:,1);
y1 = sq_amp24_freq016_d_J_tuned.Y(:,1);
y2 = sq_amp24_freq016_d_J_tuned.Y(:,2);

% Plotting
figure
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('Square Wave amp: 24V, freq: 0.16Hz, J&d-tuned')
ylabel('Velocity')
xlabel('Time')

%% 7
% Collect data
load('./Datafiles/sq_amp24_freq016_d_tuned');
x = sq_amp24_freq016_d_tuned.X(:,1);
y1 = sq_amp24_freq016_d_tuned.Y(:,1);
y2 = sq_amp24_freq016_d_tuned.Y(:,2);

% Plotting
figure
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('Square Wave amp: 24V, freq: 0.16Hz, d-tuned')
ylabel('Velocity')
xlabel('Time')

%% 8
% Collect data
load('./Datafiles/sq_amp5_freq016.mat');
x = sq_amp5_freq016.X(:,1);
y1 = sq_amp5_freq016.Y(:,1);
y2 = sq_amp5_freq016.Y(:,2);

% Plotting
figure
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('Square Wave amp: 5V, freq: 0.16Hz')
ylabel('Velocity')
xlabel('Time')

