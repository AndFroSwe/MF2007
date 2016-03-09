clear all, close all, clc;
warning('off', 'all')
%% Define parameters
n = 5; %Gearbox ratio
J1 = 1.8e-5; %Load inertia 1
J2 = 1.8e-5; %Load inertia 2
Vmax = 1; %Supply voltage
Vmin = -24; %Supply voltage
Imax = 430e-3; %Maximum current
V_i = Vmax;
V_w = Vmax;
sim_V = Vmax;
% Set up generic simulation parameters, change when using sine input or
% karnop
F_c = 0.001;
d_v = 1;
enable_sin = 0;
enable_karnop = 0;
sim_sin_amp = 1;
sim_sin_freq = 1;
sim_quantization_interval = 0;
sim_zoh_sample_time = 0;
% Motor parameters
motor_pars = struct(); % Create empty struct for motor
motor_pars.R = 112; % Terminal resistance [Ohm]
motor_pars.L = 11.4e-3;    % Terminal inductance [H]
motor_pars.d = 3.8e-6; %Viscous friction in brushes
motor_pars.k = 69.7e-3;    % Torque constant [Nm/A]
motor_pars.J_m = 7.46e-7;  % Rotor inertia

%% Exercise 1
motor = motor_pars;
J = motor.J_m + (J1 + J2)/n^2; % Calculate total inertia on motor


disp('Exercise 1')
disp('x1 = i, x2 = omega')

%-- State space representation
motor.A = [-motor.R/motor.L  -motor.k/motor.L;
    motor.k/J    -motor.d/J];
motor.B = [1/motor.L;
    0];
motor.C = [1 0;
     0 1];
D = [0; 0]; % Just to be used in ss2tf
    
disp('State space for motor')
disp('A')
disp(motor.A)
disp('B')
disp(motor.B)
disp('C')
disp(motor.C)

%Deriving transfer functions
[num, den] = ss2tf(motor.A, motor.B, [1 0], 0); % Returns tf from V to i
motor.tf_i = tf(num, den);
[num, den] = ss2tf(motor.A, motor.B, [0 1], 0); % Returns tf from V to omega
motor.tf_w = tf(num, den);
clearvars num den   % Remove variable form workspace

%-- Gets poles and zeros of both i and w
[motor.i_zeros, motor.i_poles] = zpkdata(motor.tf_i);
[motor.w_zeros, motor.w_poles] = zpkdata(motor.tf_w);
% for i
disp('Poles for i')
disp(motor.i_poles{1})
disp('Zeros for i')
disp(motor.i_zeros{1})
% for w
disp('Poles for w')
disp(motor.w_poles{1})
disp('Zeros for w')
disp(motor.w_zeros{1})

% Step response for motor i
figure
subplot(2,1,1)
step(motor.tf_i)
title('Step response for i [A]')
ylabel('i')
subplot(2,1,2)
bode(motor.tf_i)
title('Bode for i')
figure
subplot(2,1,1)
step(motor.tf_w, 1)
title('Step response for w')
ylabel('\omega [rad/s]')
subplot(2,1,2)
bode(motor.tf_w)
title('Bode for w')

% Simulink model
simtime = 0.3;    % Simulation time in seconds
sim('ex1_sim')
figure
subplot(2,2,1)
plot(sim_ex1_i)
title('Simulink: Step response for i [A]')
subplot(2,2,2)
plot(sim_ex1_w)
title('Simulink: Step response for \omega [rad/s]')
subplot(2,2,3)
plot(sim_ex1_ss_i)
title('Simulink: Step response for state space i [A]')
subplot(2,2,4)
plot(sim_ex1_ss_w)
title('Simulink: Step response for state space \omega [rad/s]')
