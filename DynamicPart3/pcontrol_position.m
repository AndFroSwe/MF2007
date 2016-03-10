close all, clear all, clc
warning('off', 'all')
%% P controller
% Load parameters
load('motor_parameters.mat')
m = motor_pars;
I = 0;
s = tf('s');
%% Create model function
Jtot = m.J + (J1 + J2)/n^2;

disp('Open loop system')
% Transfer of motor without indctance
Go = tf([m.k/(m.R*Jtot)], [1 (m.d/Jtot + m.k^2/(m.R*Jtot))]);
Go = Go*1/n*1/s % Add this to get gear box in model

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
sim('twodof_position')
figure(100)
hold on
grid on
plot(sim_output.Time, sim_output.Data, 'g')
legend('Transfer function', 'Model')

% P controller
P = 4;
disp('Closed loop')
simtime = 0.5;
sim_v = 1;
enable_karnop = 0;
enable_sin = 0;
T = 1;
S = P;
R = 1;
Gc = minreal(P*Go/(1 + P*Go))
fprintf('Pole in %0.2f\n', pole(Gc))
sim('twodof_position')
figure
hold on
grid on
plot(sim_output.Time, sim_output.Data)
title(sprintf('Feedback with P controller, P=%0.2f', P))
Gc_info = stepinfo(Gc);
fprintf('Rise time of closed system %0.2f\n', Gc_info.RiseTime)
figure 
bode(Gc)
title('Bode of closed system')


% Plot with sine wave
disp('Closed loop')
simtime = 30;
enable_karnop = 0;
enable_sin = 1;
sim_sin_amp = 20;
sim_sin_freq = 0.2;
T = P;
S = P;
R = 1;
sim('twodof_position')
figure
plot(sim_output.Time, sim_output.Data)
grid on
hold on
plot(sim_reference.Time, sim_reference.Data)
title(sprintf('Feedback with P controller, P=%0.2f', P))
legend('Output', 'Reference')

%% Discrete time controller
F = P;
% Set parameters
enable_karnop = 0;  % Dont use karnop
enable_sin = 1;     % Set 1 to enable sine input
sim_sin_amp = 10;
sim_sin_freq = 1;
sim_v = 1;
sim_zoh = 0.02;
pulses_per_rev = 1000;   % Pulses per revolution [-]
simtime = 10;
% Calculated parameters
sim_quantization_interval = 2*pi/pulses_per_rev;    % Ppr to degrees

% Simulate
sim('motor_discrete_position.slx')
figure
plot(sim_reference) 
hold on 
grid on
plot(sim_output)
title('Discrete feedback: Closed loop P controller for DC motor, output velocity')
legend('Reference', 'Output')
xlabel('Time [s]')
ylabel('\omega [rad/s]')

% sample time 0.02
G_d1 = c2d(Go,0.02,'zoh');
F_d1 = F;
Gc_d1 =minreal( G_d1*F_d1/(1+G_d1*F_d1));
figure
step(Gc_d1)
figure
pzmap(Gc_d1)
grid on

% Sample time 0.002
G_d2 = c2d(Go,0.002,'zoh');
F_d2 = P;
Gc_d2 =minreal( G_d2*F_d2/(1+G_d2*F_d2));
figure
step(Gc_d2)

figure
pzmap(Gc_d2)
grid on


