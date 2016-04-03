close all, clear all, clc
% MOTOR 4
warning('off', 'all')
%% Define parameters
n = 5; %Gearbox ratio
J1 = 1.8e-5; %Load inertia 1
J2 = 1.8e-5; %Load inertia 2
Vmax = 24; %Supply voltage
Vmin = -24; %Supply voltage
Imax = 430e-3; %Maximum current
V_i = Vmax;
V_w = Vmax;
sim_v = Vmax;
% Set up generic simulation parameters, change when using sine input or
% karnop
F_c = 1e-3;
d_v = 1;
enable_sin = 1;
enable_karnop = 1;
sim_sin_amp = 1;
sim_sin_freq = 1;
sim_quantization_interval = 0;
sim_zoh_sample_time = 0;
r0 = 0;     % Filter coefficient in controller model
% Motor parameters
motor_pars = struct(); % Create empty struct for motor
motor_pars.R = 112; % Terminal resistance [Ohm]
motor_pars.L = 11.4e-3;    % Terminal inductance [H]
motor_pars.d = 3.8e-6; %Viscous friction in brushes
motor_pars.k = 69.7e-3;    % Torque constant [Nm/A]
motor_pars.J = 7.46e-7;  % Rotor inertia

motor = motor_pars;
Ts = 0.002

 J1 = 0.0006;  % Load inertia (separated from motor inertia
 motor.d = 1e-5; % Measured at amplitude 24
 F_c_upper = 1.5e-3; % Upper static friction limit
 F_c_lower = 1.5e-3; % Lower static friction limit
 F_c = 1.5e-3;

Jtot = motor.J + J1/n^2;

%% 1.2: Model Following Control: Level 1
%       Position Controller
close all;
s = tf('s');
Go = tf([motor.k/(motor.R*Jtot)], [1 (motor.d/Jtot + motor.k^2/(motor.R*Jtot))])

% Transfer of motor without indctance
Go_p = Go*1/s


% Parameters for Maple
a_p = Go_p.num{1}(3);
b_p = Go_p.den{1}(2);

% Error feedback
% Place poles
omega1 = 10;
omega2 = 50;

Zeta1 = 0.7;
Zeta2 = 1;

r0 = 2*Zeta1*omega1+2*Zeta2*omega2-b_p;
s0 = omega1^2*omega2^2/a_p;
s1 = 2*omega1*omega2*(Zeta1*omega2+Zeta2*omega1)/a_p;
s2 = (4*Zeta1*Zeta2*omega1*omega2-2*Zeta1*b_p*omega1-2*Zeta2*b_p*omega2+b_p^2+omega1^2+omega2^2)/a_p;

% Controller parameters, PID controller
S_vector_p = [s2 s1 s0];
R_vector_p = [1 r0 0];

% Controller tf
F_p = tf(S_vector_p, R_vector_p);
disp('Error feedback closed loop')
Gc_error_p = minreal(F_p*Go_p/(1 + F_p*Go_p))

figure
step(Gc_error_p)

%% Finding Max acceleration and velocity

% If max input torque is +Mmax then max acceleration is
% amax = Mmax/Jtot
%Max velocity is Msat/(d+Fc)
% TODO: find maximum torque
% TODO: calulate maximum speed
% TODO: calculate maximum acceleration
% TODO: build signal block in simulink
% TODO: find t1
% TODO: find t2
% TODO: xxx incorporate trajectory control with model

v_max = 230;
a_max = 543;
t1 = v_max/a_max
rs = 100;
t2 = rs/v_max - v_max/a_max + t1
