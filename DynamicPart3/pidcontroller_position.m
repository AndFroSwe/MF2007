close all, clear all, clc
warning('off', 'all')
%% PID controller
% Load parameters
load('motor_parameters.mat')
m = motor_pars;
s = tf('s');
%% Create model function
Jtot = m.J + (J1 + J2)/n^2;

disp('Open loop system')
% Transfer of motor without indctance
Go = tf([m.k/(m.R*Jtot)], [1 (m.d/Jtot + m.k^2/(m.R*Jtot))]);
Go = minreal(Go*1/n*1/s) % Add this to get gear box in model


% Error feedback
% Place poles
omega1 = 30;
omega2 = 40;
a = Go.num{1}(3)
b = Go.den{1}(2)
Zeta1 = 0.7;
Zeta2 = 0.7;
r0 = 2*Zeta1*omega1+2*Zeta2*omega2-b ;
s0 = omega1^2*omega2^2/a; 
s1 = 2*omega1*omega2*(Zeta1*omega2+Zeta2*omega1)/a;
s2 = (4*Zeta1*Zeta2*omega1*omega2-2*Zeta1*b*omega1-2*Zeta2*b*omega2+b^2+...
    omega1^2+omega2^2)/a;

% Controller parameters
s = tf('s');
S = [s2 s1 s0];
T = S;
R = [1 r0 0];

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
sim('twodof_position')
figure(100)
plot(sim_output.Time, sim_output.Data, 'b')
grid on
hold on
plot(sim_reference.Time, sim_reference.Data, 'r')
title(sprintf('Error feedback with PID controller, s2=%0.2f, s1=%0.2f, s0=%0.2f and r0=%0.2f',s2, s1, s0, r0))

% Output feedback
t0 = (a/omega1^2)^-1;
T = t0*[1 2*Zeta2*omega2 omega2^2];

a = tf(Go.den{1}, [1]);
b = tf(Go.num{1}, [1]);
t = tf(T, [1]);
r = tf(R, [1]);
s = tf(S, [1]);

% Transfer function data
Gc_output = minreal((b*t)/(a*r + b*s))
figure
pzmap(Gc_output)
title('Output feedpag pole zero map')
grid on

% Simulate
enable_karnop = 0;
enable_sin = 1;
sim_sin_amp = 20;
sim_sin_freq = 2;
sim_v = 10;
simtime = 10;
sim('twodof_position')
figure(100)
plot(sim_output.Time, sim_output.Data, 'g')
grid on
hold on
title(sprintf('Output feedback with PID controller, s2=%0.2f, s1=%0.2f, s0=%0.2f and r0=%0.2f',s2, s1, s0, r0))
legend('Error', 'Reference', 'Output')

%% Discrete time controller
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
sim('motor_discrete_position.slx')
figure
plot(sim_reference) 
hold on 
grid on
plot(sim_output)
title('Discrete feedback: Closed loop PID controller for DC motor, output position')
legend('Reference', 'Output')
xlabel('Time [s]')
ylabel('\omega [rad/s]')

% sample time 0.02
G_d1 = c2d(Go,0.02,'zoh');
F_d1 = c2d(s/r,0.02,'tustin');
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

