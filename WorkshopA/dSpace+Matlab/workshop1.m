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

%% 1: Parameter identification

% Estimated parameters
J1 = 0.00075;  % Load inertia (separated from motor inertia
motor.d = 3e-5; % Measured at amplitude 10

%% 2: parameter identification, with karnop
% Start with high speed, 24 v,  and estimating d. Fc has lower effect there.
% Then go down to 5 v and find Fc lower and upper.
J1 = 0.0006;  % Load inertia (separated from motor inertia
motor.d = 1.5e-5; % Measured at amplitude 10
F_c_upper = 1.5e-3; % Upper static friction limit
F_c_lower = 0.5e-3; % Lower static friction limit

%% 4: Controlling the motor
%% 4.1: Velocity Controller
Jtot = motor.J + J1/n^2;
disp('Open loop system')

% Transfer of motor without indctance
Go = tf([motor.k/(motor.R*Jtot)], [1 (motor.d/Jtot + motor.k^2/(motor.R*Jtot))])

% Parameters for Maple
a = Go.num{1}(2)
b = Go.den{1}(2)

% Error feedback
% Place poles
omega1 = 10;
omega2 = 5;

% Calculate regulator parameters
s1 = -(b-omega1-omega2)/a; % P 
s2 = omega1*omega2/a; % I

% Controller parameters, PI controller
S_vector = [s1 s2];
R_vector = [1 0];

% Controller tf
F = tf(S_vector, R_vector);
disp('Error feedback closed loop')
Gc_error = minreal(F*Go/(1 + F*Go))
figure
pzmap(Gc_error)
grid on
title('PZ map for error feedback system')

% Output feedback
% Calculate T
t0 = dcgain(tf(Go.num{1}, [1 omega1]))^-1;
T_vector = t0*[1 omega2];

A = tf(Go.den{1}, [1]);
B = tf(Go.num{1}, [1]);
T = tf(T_vector, [1]);
R = tf(R_vector, [1]);
S = tf(S_vector, [1]);
Gc_output = minreal((B*T)/(A*R + B*S))
figure
pzmap(Gc_output)
title('Output feedback pole zero map')
grid on

%% Discretization
% Calculate sample time
samples_per_risetime = 10;
Gc_info = stepinfo(Gc_output);
fprintf('Rise time is %0.2f ms\n', Gc_info.RiseTime*1000)
sample_time = Gc_info.RiseTime/samples_per_risetime
% Parameter for program. Set manually after viewing the above
Ts = 5.5e-2;
Ts = sample_time;
% Make discrete
Go_d  = minreal(c2d(Go, Ts,'zoh'))
Gff_d = minreal(c2d(T/R, Ts, 'tustin'))
Gfb_d = minreal(c2d(S/R, Ts, 'tustin'))

% Model parameters
pulses_per_rev = 1000; % Defined on motor
quant = 2*pi/pulses_per_rev;    % Ppr to degrees

% Discrete system
Gyr_d = minreal((Go_d*Gff_d)/(1+Go_d*Gfb_d))
figure
pzmap(Gyr_d)
grid on
title('Discrete poles of output feedback')
figure
step(Gyr_d)

% Compare continuous and discrete
figure
step(Gc_output)
hold on
grid on
step(Gyr_d)


%% 4.2: Position Controller
s = tf('s');
% Transfer of motor without indctance
Go_p = Go*1/s


% Parameters for Maple
a_p = Go_p.num{1}(3);
b_p = Go_p.den{1}(2);

% Error feedback
% Place poles
omega1 = 9;
omega2 = 50;

Zeta1 = 1;
Zeta2 = 0.7;

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
pzmap(Gc_error_p)
grid on
title('PZ map for error feedback system')

% Output feedback
% Calculate T
t0_p = dcgain(tf(Go_p.num{1}, [1 2*Zeta1*omega1 omega1^2]))^-1;
T_vector_p = t0_p*[1 2*Zeta1*omega2 omega2^2];

% Controller polynomials
A_p = tf(Go_p.den{1}, [1]);
B_p = tf(Go_p.num{1}, [1]);
T_p = tf(T_vector_p, [1]);
R_p = tf(R_vector_p, [1]);
S_p = tf(S_vector_p, [1]);
Gc_output_p = minreal((B_p*T_p)/(A_p*R_p + B_p*S_p))
figure
pzmap(Gc_output_p)
title('Output feedback pole zero map')
grid on

%% Discretization
% Calculate sample time
samples_per_risetime = 10;
Gc_info_p = stepinfo(Gc_output_p);
fprintf('Rise time is %0.2f ms\n', Gc_info_p.RiseTime*1000)
sample_time = Gc_info_p.RiseTime/samples_per_risetime

% Parameter for program. Set manually after viewing the above
Ts_p = sample_time;

% Make discrete
Go_d_p  = minreal(c2d(Go_p, Ts_p,'zoh'))
Gff_d_p = minreal(c2d(T_p/R_p, Ts_p, 'tustin'))
Gfb_d_p = minreal(c2d(S_p/R_p, Ts_p, 'tustin'))

% Model parameters
pulses_per_rev = 1000; % Defined on motor
quant = 2*pi/pulses_per_rev;    % Ppr to degrees

% Discrete system
Gyr_d_p = minreal((Go_d_p*Gff_d_p)/(1+Go_d_p*Gfb_d_p))
figure
pzmap(Gyr_d_p)
grid on
title('Discrete poles of output feedback')


% Compare continuous and discrete
figure
step(Gc_output_p)
hold on
grid on
step(Gyr_d_p)
title('Comparison between discrete and continuous output feedback system')
stepinfo(Gyr_d_p)

% Sensitivity Function
G_s = 1/(1+(Go_p*(S_p/R_p))); %Sensitivity Function
G_k = 1 - G_s;
figure
bode(G_s)
grid on
hold on
bode(G_k)
legend('Sensitivity','Complementary')
title('Sensitivy function check')
Ts = Ts_p