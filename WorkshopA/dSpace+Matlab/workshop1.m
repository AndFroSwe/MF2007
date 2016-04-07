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

%% 1: Parameter identification

% Estimated parameters
J1 = 0.00006;  % Load inertia (separated from motor inertia
motor.d = 1.35e-5; % Measured at amplitude 24

%% 2: parameter identification, with karnop
% Start with high speed, 24 v,  and estimating d. Fc has lower effect there.
% Then go down to 5 v and find Fc lower and upper.
 J1 = 0.0006;  % Load inertia (separated from motor inertia
 motor.d = 1e-5; % Measured at amplitude 24
 F_c_upper = 1.5e-3; % Upper static friction limit
 F_c_lower = 1.5e-3; % Lower static friction limit
 F_c = 1.5e-3;

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
close all
disp('discrete velocity controller')
% Calculate sample time
samples_per_risetime = 10;
Gc_info = stepinfo(Gc_output);
fprintf('Rise time is %0.2f ms\n', Gc_info.RiseTime*1000)
sample_time = Gc_info.RiseTime/samples_per_risetime;
% Parameter for program
Ts = sample_time
% Make discrete
disp('discretiziced controller')
Go_d  = minreal(c2d(Go, Ts,'zoh'))
Gff_d = minreal(c2d(T/R, Ts, 'tustin'))
Gfb_d = minreal(c2d(S/R, Ts, 'tustin'))
% place discrete poles
z = tf('z')

% parameters for maple
b = Go_d.den{1}(2);
a = Go_d.num{1}(2);

% pole placement
p1 = 0.65;
p2 = 0.95;

% from maple
s0 = (p1*p2+b)/a;
s1 = -(b+p1+p2-1)/a;

% output feedback polynomials
Sd = s1*z + s0;
Rd = z-1;
t0 = dcgain(a/(z-p1))^-1;
Td = (z-p2)*t0;

% add polynomials for simulation in simulate_motor_controllers.slx
T_sim = Td.num{1};
R_sim = Rd.num{1};
S_sim = Sd.num{1};

% closed loop polynomial
Gff_dead = Td/Rd;
Gfb_dead = Sd/Rd;
Gyr_dead = minreal((Go_d*Gff_dead)/(1+Go_d*Gfb_dead));

% Model parameters
pulses_per_rev = 1000; % Defined on motor
quant = 2*pi/pulses_per_rev;    % Ppr to degrees

% Discrete system
% discretiziced continuous system
Gyr_d = minreal((Go_d*Gff_d)/(1+Go_d*Gfb_d))
figure
pzmap(Gyr_d)
grid on
title('Discrete poles of output feedback')
figure
step(Gyr_d)
hold on
step(Gyr_dead)
legend('discreizised', 'discrete pole placement')
% Compare continuous and discrete
% figure
% step(Gc_output)
% hold on
% grid on
% step(Gyr_d)


%% 4.2: Position Controller
close all, clc
% PID position controller
% output feedback

s = tf('s');
% Transfer of motor without indctance
Go_p = Go*1/s       % position is velocity integrated 
wb = 5.78;          % bandwidth of open loop system [rad/s]
ws = 10*wb;

Ts = 2*pi/ws;

% Make system discrete
Go_z = c2d(Go_p, Ts, 'zoh')

% output feedback plant parameters
% numerator
b1 = Go_z.num{1}(2)
b0 = Go_z.num{1}(3)
B = tf([0 b1 b0], [0 0 1], Ts)
% denominator
a1 = Go_z.den{1}(2)
a0 = Go_z.den{1}(3)
A = tf([1 a1 a0], [0 0 1], Ts)

% output feedback
% Place poles of  discrete closed system
p1 = 0.1; % Am pole 1
p2 = 0.1;   % Am pole 2
Am = tf([1 -p1-p2 p1*p2], [0 1], Ts)

p3 = 0; % observer polynomial poles
p4 = 0;   
Ao = tf([1 -p3-p4 p3*p4], [0 1], Ts)

% parameter for integral feedback
Kb = 10;

% calulate pid parameters
r0 = (-b1^3*p1*p2*p3*p4-b0*b1^2*p1*p2*p3-b0*b1^2*p1*p2*p4-b0*b1^2*p1*p3*p4-b0*b1^2*p2*p3*p4-b0^2*b1*p1*p2-b0^2*b1*p1*p3-b0^2*b1*p1*p4-b0^2*b1*p2*p3-b0^2*b1*p2*p4-b0^2*b1*p3*p4+a0*b0^2*b1+a0*b0*b1^2-a1*b0^3-a1*b0^2*b1-b0^3*p1-b0^3*p2-b0^3*p3-b0^3*p4+b0^3)/(a0*b0*b1^2+a0*b1^3-a1*b0^2*b1-a1*b0*b1^2+b0^3+b0^2*b1)
s0 = (a0*b1^2*p1*p2*p3*p4-a1*b0*b1*p1*p2*p3*p4-a1*b1^2*p1*p2*p3*p4-a0*b1^2*p1*p2*p3-a0*b1^2*p1*p2*p4-a0*b1^2*p1*p3*p4-a0*b1^2*p2*p3*p4+b0^2*p1*p2*p3*p4+b0*b1*p1*p2*p3*p4-a0*b0*b1*p1*p2-a0*b0*b1*p1*p3-a0*b0*b1*p1*p4-a0*b0*b1*p2*p3-a0*b0*b1*p2*p4-a0*b0*b1*p3*p4+a0^2*b0*b1+a0^2*b1^2-a0*a1*b0^2-a0*a1*b0*b1-a0*b0^2*p1-a0*b0^2*p2-a0*b0^2*p3-a0*b0^2*p4+a0*b0^2)/(a0*b0*b1^2+a0*b1^3-a1*b0^2*b1-a1*b0*b1^2+b0^3+b0^2*b1)
s1 = -(-a1*b1^2*p1*p2*p3*p4-a1*b0*b1*p1*p2*p3-a1*b0*b1*p1*p2*p4-a1*b0*b1*p1*p3*p4-a1*b0*b1*p2*p3*p4+b0*b1*p1*p2*p3*p4+b1^2*p1*p2*p3*p4-a0*b0*b1*p1*p2-a0*b0*b1*p1*p3-a0*b0*b1*p1*p4-a0*b0*b1*p2*p3-a0*b0*b1*p2*p4-a0*b0*b1*p3*p4-a0*b1^2*p1*p2-a0*b1^2*p1*p3-a0*b1^2*p1*p4-a0*b1^2*p2*p3-a0*b1^2*p2*p4-a0*b1^2*p3*p4+a1*b0*b1*p1*p2+a1*b0*b1*p1*p3+a1*b0*b1*p1*p4+a1*b0*b1*p2*p3+a1*b0*b1*p2*p4+a1*b0*b1*p3*p4+b0^2*p1*p2*p3+b0^2*p1*p2*p4+b0^2*p1*p3*p4+b0^2*p2*p3*p4+b0*b1*p1*p2*p3+b0*b1*p1*p2*p4+b0*b1*p1*p3*p4+b0*b1*p2*p3*p4+a0^2*b0*b1+a0^2*b1^2-a0*a1*b0^2-2*a0*a1*b0*b1-a0*a1*b1^2-a0*b0^2*p1-a0*b0^2*p2-a0*b0^2*p3-a0*b0^2*p4-a0*b0*b1*p1-a0*b0*b1*p2-a0*b0*b1*p3-a0*b0*b1*p4+a1^2*b0^2+a1^2*b0*b1+a1*b0^2*p1+a1*b0^2*p2+a1*b0^2*p3+a1*b0^2*p4-a1*b0^2)/(a0*b0*b1^2+a0*b1^3-a1*b0^2*b1-a1*b0*b1^2+b0^3+b0^2*b1)
s2 = -(-b1^2*p1*p2*p3*p4-b0*b1*p1*p2*p3-b0*b1*p1*p2*p4-b0*b1*p1*p3*p4-b0*b1*p2*p3*p4+a0*a1*b0*b1+a0*a1*b1^2+a0*b0*b1*p1+a0*b0*b1*p2+a0*b0*b1*p3+a0*b0*b1*p4+a0*b1^2*p1+a0*b1^2*p2+a0*b1^2*p3+a0*b1^2*p4-a1^2*b0^2-a1^2*b0*b1-a1*b0^2*p1-a1*b0^2*p2-a1*b0^2*p3-a1*b0^2*p4-a1*b0*b1*p1-a1*b0*b1*p2-a1*b0*b1*p3-a1*b0*b1*p4-b0^2*p1*p2-b0^2*p1*p3-b0^2*p1*p4-b0^2*p2*p3-b0^2*p2*p4-b0^2*p3*p4+a0*b0^2-a0*b1^2+a1*b0^2+a1*b0*b1+b0^2*p1+b0^2*p2+b0^2*p3+b0^2*p4-b0^2)/(a0*b0*b1^2+a0*b1^3-a1*b0^2*b1-a1*b0*b1^2+b0^3+b0^2*b1)

% Controller polynomials, PID controller
Sd = s2*z^2 + s1*z + s0;
Rd = (z - 1)*(z + r0);

% calculate T
t0 = dcgain(B/(Am))^-1;
Td = Ao*t0;

% closed loop system
Gc_z = minreal(B*t0/(Am))

% pzmaps and step responses
disp('closed loop poles')
pole(Gc_z)
disp('observer poles')
zero(Ao)
figure
step(Gc_z)

% add polynomials for controller
T_sim = Td.num{1};
R_sim = Rd.num{1};
S_sim = Sd.num{1};

% parameters for anti windup of feedback
c0 = (s2 + s1 + s0)/(1 + r0);
d1 = s2;
d0 = (r0*(s1 + s2) - s0)/(1 + r0);

% parameters for anti windup of feedback
s2_ = Td.num{1}(1)
s1_ = Td.num{1}(2)
s0_ = Td.num{1}(3)

c0_ = (s2_ + s1_ + s0_)/(1 + r0);
d1_ = s2_;
d0_ = (r0*(s1_ + s2_))/(1 + r0);



disp('pbd part')
tf([d1 d0], [1 r0], Ts) + tf([0 c0], [1 -1], Ts)
disp('S/R')
Sd/Rd

% run simulation
simtime = 1;
% sim('Simulate_position_motor_controllers.slx')
sim('Simulate_cascsaded_motor_controllers.slx')
% plot response
figure
subplot(2,1,1)
plot(sim_reference.Time, sim_reference.Data)
hold on
grid on
plot(sim_position.Time, sim_position.Data)
title('step response for position')
legend('reference', 'position')
xlabel('t')
ylabel('position [rad]')

% plot pzmap
subplot(2,1,2)
pzmap(Gc_z)
grid on

zero(A*Rd + B*Sd)
% 
% % plot saturation
% figure
% plot(sim_saturation)
% title('saturation')
% 
% 
%


Ts
















