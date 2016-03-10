close all, clear all, clc
warning('off', 'all')
%% PI controller
% Load parameters
load('motor_parameters.mat')
m = motor_pars;

%% Create model function
Jtot = m.J + (J1 + J2)/n^2;

disp('Open loop system')
% Transfer of motor without indctance
Go = tf([m.k/(m.R*Jtot)], [1 (m.d/Jtot + m.k^2/(m.R*Jtot))]);
Go = Go*1/n % Add this to get gear box in model


% Error feedback
% Place poles
omega1 = 400;
omega2 = 500;

P = n*(Jtot*omega1*m.R+Jtot*omega2*m.R-m.d*m.R-m.k^2)/m.k
I = omega1*omega2*n*Jtot*m.R/m.k
 
% Controller parameters
s = tf('s');
S = [P I];
T = S;
R = [1 0];

% Controller tf
F = tf(S, R);
disp('Error feedback closed loop')
Gc_error = minreal(F*Go/(1 + F*Go))
figure
pzmap(Gc_error)
title('PZ map for error feedback system')

% Simulate
enable_karnop = 0;
enable_sin = 1;
sim_sin_amp = 20;
sim_sin_freq = 2;
sim_v = 10;
simtime = 10;
sim('twodof_velocity')
figure(100)
plot(sim_output.Time, sim_output.Data, 'b')
grid on
hold on
plot(sim_reference.Time, sim_reference.Data, 'r')
title(sprintf('Error feedback with PI controller, P=%0.2f and I=%0.2f', P, I))

% Output feedback
% Calculate T
t0 = dcgain(tf(Go.num{1}, [1 omega1])/n)^-1;
T = t0*[1 omega2];

a = tf(Go.den{1}, [1]);
b = tf(Go.num{1}, [1]);
t = tf(T, [1]);
r = tf(R, [1]);
s = tf(S, [1]);
Gc_output = minreal((b*t)/(a*r + b*s))
figure
pzmap(Gc_output)
title('Output feedpag pole zero map')
grid on

% Simulate
enable_karnop = 0;
enable_sin = 1;
sim_v = 10;
simtime = 0.5;
sim('twodof_velocity')
figure(100)
plot(sim_output.Time, sim_output.Data, 'g')
grid on
hold on
title(sprintf('Output feedback with PI controller, P=%0.2f and I=%0.2f', P, I))
legend('Error feedback', 'Reference', 'Output feedback')

% Step responses
figure
step(Gc_output)
hold on
step(Gc_error)
title('Step response')

%% Discrete time controller
close all
% Set parameters
enable_karnop = 0;  % Dont use karnop
enable_sin = 1;     % Set 1 to enable sine input
sim_sin_amp = 10;
sim_sin_freq = 1;
sim_v = 1;
sim_zoh = 0.002;
pulses_per_rev = 1000;   % Pulses per revolution [-]
simtime = 10;
% Calculated parameters
sim_quantization_interval = 2*pi/pulses_per_rev;    % Ppr to degrees

% Simulate
sim('motor_discrete_velocity.slx')
figure
plot(sim_reference) 
hold on 
grid on
plot(sim_output)
title('Discrete feedback: Closed loop PI controller for DC motor, output velocity')
legend('Reference', 'Output')
xlabel('Time [s]')
ylabel('\omega [rad/s]')

% sample time 0.02
G_d1 = c2d(Go,0.02,'zoh');
F_d1 = c2d(F,0.02,'tustin');
Gc_d1 =minreal( G_d1*F_d1/(1+G_d1*F_d1));
figure
step(Gc_d1)
figure
pzmap(Gc_d1)
grid on

% Sample time 0.002
G_d2 = c2d(Go,0.002,'zoh');
F_d2 = c2d(F,0.002,'tustin');
Gc_d2 =minreal( G_d2*F_d2/(1+G_d2*F_d2));
figure
step(Gc_d2)

figure
pzmap(Gc_d2)
grid on

