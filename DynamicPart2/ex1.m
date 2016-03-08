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
disp('Exercise 1')
motor = motor_pars;

J = motor.J_m + (J1 + J2)/n^2; % Calculate total inertia on motor
disp('x1 = i, x2 = omega')
% State space representation
disp('State space of motor')
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

%% Exercise 2
J = (J1 + J2);
disp('Exercise 2')
motor_L = motor_pars;
motor_L.L = 0;

% Simulate model to get data
disp('Simulating ex2...')
simtime = 5;
sim_step_v = 1;
enable_sin = 0;
sim('sim_ex2.slx');

% Voltage control
% Transfer function
disp('Transfer function')
motor_L.tf_w = tf([motor_L.k], [(motor_L.J_m + J/n^2)*motor_L.R (motor_L.k^2 + motor_L.d*motor_L.R)]);

figure
step(motor_L.tf_w)
hold on
plot(sim_ex2_v_w.Time, sim_ex2_v_w.Data, 'g')
hold on
step(motor.tf_w)
title('Step for voltage controlled DC motor')
legend('No inductance, tf', 'No inductance, model', 'Inductance')
figure
pzmap(motor_L.tf_w)
title('PZ map for voltage controlled DC motor with no inductance')

% Current control
motor_L.tf_i = tf([motor_L.k], [(motor_L.J_m + J/n^2) motor_L.d]);
figure
step(motor_L.tf_i)
title('Step for DC motor with i control')
figure
pzmap(motor_L.tf_i)
title('PZ map for DC motor with i control')

%% Ex 3 With Karnopp model for friction

%For step inputs
sim_step_v = 2.38;
% For sine inputs
sim_sin_amp = 10;
sim_sin_freq = 1;
enable_sin = 1;
% With Karnopp
F_c = 0.001;
d_v = 10;
enable_karnop = 1;

% Create atomatic string for title
if enable_sin
    title_string = sprintf('Sine input with f=%0.1f rad/s and A=%0.1f V with Karnop',...
        sim_sin_freq, sim_sin_amp);
else
    title_string = sprintf('Step input with A=%0.1f V with Karnop',...
        sim_step_v);
end
simtime = 10;
sim('sim_ex2.slx')
figure
% Plot resulting velocity
plot(sim_ex2_v_w.Time, sim_ex2_v_w.Data);
title(title_string)
grid on

simtime = 3;
sim_step_v = 1;
enable_sin = 0;
sim('sim_ex2.slx')
figure
plot(sim_ex2_v_w.Time,sim_ex2_v_w.Data);
title('Step input with A=1 V with Karnop')

sim_step_v=10;
sim('sim_ex2.slx')

figure
plot(sim_ex2_v_w.Time,sim_ex2_v_w.Data);
title('Step input with A=10 V with Karnop')
simtime = 10;
% %% part 4: Quantizing
% % Set parameters
% enable_sin = 0;     % Set 1 to enable sine input
% zoh_sample_time = 1;   % Sample time in zoh [ms]
% pulses_per_rev = 512;   % Pulses per revolution [-]
%     
% 
% % Calculated parameters
% enable_karnop = 0;  % Dont use karnop
% sim_quantization_interval = 2*pi/pulses_per_rev;    % Ppr to degrees
% sim_zoh_sample_time = zoh_sample_time*1e-3;  % Sample time, from ms to s
% 
% % Simulate
% simtime = 1; % Sim for 1 s
% sim('sim_ex2.slx')
% % Plot of unquantized signal
% figure
% plot(sim_ex2_v_w.Time, sim_ex2_v_w.Data)
% hold on
% stairs(sim_ex2_v_w_sampled.Time, sim_ex2_v_w_sampled.Data, 'r')
% grid on
% title('Motor control with and without quantization')
% xlabel('Time [s]')
% ylabel('\omega [rad/s]')
% legend('Unquantized velocity', 'Quantized velocity')









