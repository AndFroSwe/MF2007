close all, clear all, clc
Ts = 0.002;
% TODO: PID controller
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

% motor_pars.d = 8e-6; %Viscous friction in brushes
% motor_pars.J = 10e-6;  % Rotor inertia
% % J1 = 3e-5; %Load inertia 1
% J2 = 3e-5; %Load inertia 2
J = J1+J2;
Jtot = motor.J + J/n^2; % Total inertia including load inertia after gear



%% Parameter identification

Jtot = 1/45000;
F_c = 0.0008;
motor.d = 2e-5;
figure
load('S.mat');
x = S.X(:,1);
y1 = S.Y(:,1);
y2 = S.Y(:,2);
plot(x.Data,y1.Data,x.Data,y2.Data)
legend('Model','Real')
title('Linear Amplitude 10')
ylabel('Position')
xlabel('Time')
figure
subplot(3,1,1)

load('3_10amp_sin.mat');
x = amp_sin.X(:,1);
y1 = amp_sin.Y(:,1);
y2 = amp_sin.Y(:,2);
plot(x.Data,y1.Data,x.Data,y2.Data)
legend('Model','Real')
title('Sinewave Amplitude 10')
ylabel('Position')
xlabel('Time')
subplot(3,1,2)

load('3_10amp_step.mat');
x = amp_step.X(:,1);
y1 = amp_step.Y(:,1);
y2 = amp_step.Y(:,2);
plot(x.Data,y1.Data,x.Data,y2.Data)
% legend('Model','Real')
title('Squarewave Amplitude 10')
ylabel('Position')
xlabel('Time')
subplot(3,1,3)

load('3_20amp_step.mat');
x = amp_step.X(:,1);
y1 = amp_step.Y(:,1);
y2 = amp_step.Y(:,2);
plot(x.Data,y1.Data,x.Data,y2.Data)
% legend('Model','Real')
title('Squarewave Amplitude 20')
ylabel('Position')
xlabel('Time')

%% Velocity Control

s = tf('s');
G_nom = motor.k;
G_den = (s*Jtot + motor.d)*(motor.R) + motor.k;
G = G_nom/G_den;
P = 3;
F_P= P;

Gc_P = minreal(F_P*G/(1 + F_P*G));
p1 = pole(Gc_P);
%  figure
%  rlocus(Gc_P)
 axis([-100 100 -100 100])
%  p1 = rlocfind(Gc_P)
omega = abs(p1);
zeta = 0.9;
P = (2*motor.J*motor.R*omega*zeta - motor.k - motor.d*motor.R)/motor.k%-(2*p1*motor.R*Jtot + motor.k + motor.d*motor.R)/motor.k
I = (motor.J*motor.R*omega^2)/motor.k%(p1^2*Jtot*motor.R)/motor.k
 P = 4;
 I = 1;

F_PI = P + 1/s*I;
Gc_PI = minreal((F_PI*G)/(1+F_PI*G));

enable_sin = 0;     % Set 1 to enable sine input
zoh_sample_time = 0.002;   % Sample time in zoh [ms]
pulses_per_rev = 1000;   % Pulses per revolution [-]
sim_zoh = 0.02;    

% Calculated parameters
enable_karnop = 0;  % Dont use karnop
sim_quantization_interval = 2*pi/pulses_per_rev;    % Ppr to degrees
sim_zoh_sample_time = zoh_sample_time*1e-3;  % Sample time, from ms to s
G_d = c2d(G,0.002,'zoh');
F_d = c2d(F_PI,0.002,'tustin');
Gc_d =minreal( G_d*F_d/(1+G_d*F_d));

p = pole(Gc_PI);
p1 = p(1);
p2 = p(2);
%% Position Control
% close all;
T = 1;
R = 1;
S = 1;
P = 81;
G_nom = motor.k;
G_den = (s*Jtot + motor.d)*(motor.R) + motor.k;
G = G_nom/G_den*1/s;

F_P= P;
Gc_P = minreal(F_P*G/(1 + F_P*G));
p = pole(Gc_P)

omega = real(abs(p1));
omega2 = real(abs(p2));
zeta =0.9;

% Because of Maple
J = Jtot;
r = motor.R;
d = motor.d;
k = motor.k;

% Parameters from Maple "PIDcontroller.mw"
P = abs(J^2*omega*r^2*(2*zeta*omega2+omega)/(k*(J*r-d*r-k)));
I = abs(omega^2*omega2*J^2*r^2/((J*r-d*r-k)*k));
D = abs((2*J^2*zeta*omega*r^2+J^2*omega2*r^2-J*d*r^2+d^2*r^2-J*k*r+2*d*k*r+k^2)/(k*(J*r-d*r-k)));
r0 = abs(J*r/(J*r-d*r-k));

% Find the PID controller and the closed loop system tf
F_PID = (D*s^2+P*s+I)/(s*(r0*s+1));
% Closed loop system
Gc_PID = minreal(F_PID*G/(1 + F_PID*G));

pole(Gc_PID);
% rlocus(Gc_PID)
% grid on
% rlocfind(Gc_PID)

% P = (4*(11*omega^2+1000))/omega^2
% I = 10000/omega^2
% D = -(omega^2-4296)/omega^2
% r0 = -44
% F_PID = (D*s^2+P*s+I)/(s*(r0*s+1));
% rlocus(minreal(F_PID*G/(1 + F_PID*G)))

T = P*s+D*s^2+I;
R = s*(1+r0*s);
S = P*s+D*s^2+I;