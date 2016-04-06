close all, clc, clear all
% PID position controller
% output feedback

s = tf('s');
Ts = 1; % Sampling time
% Transfer of motor without indctance
Go_p = Go*1/s       % position is velocity integrated 
wb = 5.78;          % bandwidth of open loop system [rad/s]
ws = 100*wb;
Ts = 2*pi/ws

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
p1 = 0.8; % Am pole 1
p2 = 0.8;   % Am pole 2
Am = tf([1 -p1-p2 p1*p2], [0 1], Ts)

p3 = 0.4; % observer polynomial poles
p4 = 0.4;   
Ao = tf([1 -p3-p4 p3*p4], [0 1], Ts)

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

% parameter for integral feedback
TI = 0.00000010000;