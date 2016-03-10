close all, clear all, clc
warning('off', 'all')
%% P controller
% Load parameters
load('motor_parameters.mat')
m = motor_pars;

%% Create model function
Jtot = m.J + (J1 + J2)/n^2;

disp('Open loop system')
% Transfer of motor without indctance
Go = tf([m.k/(m.R*Jtot)], [1 (m.d/Jtot + m.k^2/(m.R*Jtot))]);
Go = Go*1/n % Add this to get gear box in model

% tf info
figure(100)
step(Go)
title('Step response for system')
figure
pzmap(Go)
title('System poles')
Go_info = stepinfo(Go);
fprintf('Risetime of open loop system is %0.2f\n', Go_info.RiseTime)
fprintf('with pole in %0.2f\n',pole(Go))

% Construct closed loop system
figure
rlocus(Go)
title('Root locus of open loop system')
P_loc = rlocfind(Go)

% Simulation parameters
% Compare open loops
simtime = 0.5;
sim_v = 1;
enable_karnop = 0;
enable_sin = 0;
T = 1;
S = 0;
R = 1;
sim('twodof_velocity')
figure(100)
hold on
grid on
plot(sim_output.Time, sim_output.Data, 'g')
legend('Transfer function', 'Model')

% P controller
P = 8;
disp('Closed loop')
simtime = 0.5;
sim_v = 1;
enable_karnop = 0;
enable_sin = 0;
T = 1;
S = P;
R = 1;
Gc = P*Go/(1 + P*Go)
sim('twodof_velocity')
figure
hold on
grid on
plot(sim_output.Time, sim_output.Data)
title(sprintf('Feedback with P controller, P=%0.2f', P))
Gc_info = stepinfo(Gc);
fprintf('Rise time of closed system %0.2f\n', Gc_info.RiseTime)
















