clear all, close all, clc;
%% Define parameters
n = 5; %Gearbox ratio
J1 = 1.8e-5; %Load inertia 1
J2 = 1.8e-5; %Load inertia 2
Vmax = 24; %Supply voltage
Vmin = -24; %Supply voltage
Imax = 430e-3; %Maximum current
V_i = Vmax;
V_w = Vmax;
sim_V = Vmax;
% Motor parameters
motor_pars = struct(); % Create empty struct for motor
motor_pars.R = 112; % Terminal resistance [Ohm]
motor_pars.L = 11.4e-3;    % Terminal inductance [H]
motor_pars.d = 3.8e-6; %Viscous friction in brushes
motor_pars.k = 69.7e-3;    % Torque constant [Nm/A]
motor_pars.J_m = 7.46e-7;  % Rotor inertia

%% Exercise 1
disp('Exercise 1')
motor = motor_pars;

J = motor.J_m + (J1 + J2)/n^2; % Calculate total inertia on motor
disp('x1 = i, x2 = omega')
% State space representation
disp('State space of motor')
motor.A = [-motor.R/motor.L  -motor.k*n/motor.L;
    motor.k/J    -motor.d*n/J];
motor.B = [sim_V/motor.L;
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

[num, den] = ss2tf(motor.A, motor.B, [1 0], 0); % Returns tf from V to i
disp('tf for i')
motor.tf_i = tf(num, den);
motor.tf_i
[num, den] = ss2tf(motor.A, motor.B, [0 1], 0); % Returns tf from V to omega
disp('tf for w')
motor.tf_w = tf(num, den);
motor.tf_w
clearvars num den   % Remove variable form workspace

% get poles and zeros of both i and w
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
sim('sim_ex1')
figure
subplot(3,1,1)
plot(sim_ex1_i)
title('Simulink: Step response for i [A]')
subplot(3,1,2)
plot(sim_ex1_w)
title('Simulink: Step response for w [rad/s]')
subplot(3,1,3)
% plot(sim_ex1_theta)
% title('Simulink: Step response for theta')
%% Exercise 2
J = (J1 + J2);
disp('Exercise 2')
motor_L = motor_pars;
motor_L.L = 0;

% Voltage control
G_voltage = tf([motor_L.k], [(motor_L.J_m + J/n^2) (motor_L.k^2 + motor_L.d)])
step(G_voltage)

% Current control
motor_L.tf_i_controlled = tf([motor_L.k/J*Imax], [1 motor_L.k/J]);
disp('Current controlled motor tf')
motor_L.tf_i_controlled
figure 
step(motor_L.tf_i_controlled)
ylabel('\omega [rad/s]')



