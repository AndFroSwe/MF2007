close all, clear all, clc
%% 1

% Collect data
load('./Datafiles/wsA_level2_V.mat');
x = wsA_level2_V.X(:,1);
y1 = wsA_level2_V.Y(:,1);

% Plotting
figure
plot(x.Data,y1.Data)
legend('Reference','Motor')
title('Voltage approximated system')
ylabel('Velocity')
xlabel('Time')

