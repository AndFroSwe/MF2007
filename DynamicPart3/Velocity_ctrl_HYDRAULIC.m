%% Hydraulic cylinder
% Velocity controller for hydraulic system
% TODO: Verify that model works in both directions
% TODO: Design position controller in outer loop (cascaded)
% TODO: Make discrete time approximation
% TODO: Find longest sampling time
close all, clear all, clc
warning('off','all')
enable_output = 0;
%%
% Piston parameters
Dc = 0.05; % Cylinder diameter m
Dp = 0.02; %Piston rod diameter m
lp = 0.7; %maximum piston stroke m
m = 100; % total moving mass kg
uf = 200; %Linear friction coeff Ns/m
Rv = 1e-4; % Flow constant
xv = 0.003; %Valve opening -1 - 1 cm;
Ps = 20e6; %Supply pressure MPA
Pt = 0 ; %Tank return pressure MPA
poil = 1000; % Oil density kg/m^3
Tforce = 1;
B = 2e9; %Bulk modulus
A1 = (Dc/2)^2*pi; %Area of piston
A2 = (Dc/2)^2*pi - (Dp/2)^2*pi;

Volume0 = A1*lp;
Cf = Volume0/B; %Compressibility Oil

%Linearization 
Am = (A1+A2)/2;

Fe = 0; % External force N
df = uf; % Friction
syms v p1 p2

% Case if positive piston speed
if xv >= 0
    eq1 = (1/m)*(Am*(p1-p2)-Fe-df*v )==0;
    eq2 = (1/Cf)*(Rv*sqrt(Ps-p1)*xv-Am*v )==0;
    eq3 = (1/Cf)*(Am*v-Rv*sqrt(p2)*xv) == 0;
    % Solve for stationary points
    solution = solve([eq1,eq2,eq3],[v,p1,p2]);
    v0 = double(solution.v);
    p10 = double(solution.p1);
    p20 = double(solution.p2);
    R1 = -Rv*xv/(2*sqrt(Ps-p10)*Cf);
    R2 = -Rv*xv/(2*sqrt(p20)*Cf);
    K1 = Rv*sqrt(Ps-p10)/Cf;
    K2 = -Rv*sqrt(p20)/Cf;
end

% Case if negative piston speed
if xv < 0
    eq1 = (1/m)*(Am*(p1-p2)-Fe-df*v) == 0;
    eq2 = (1/Cf)*(Rv*sqrt(abs(p1))*xv-Am*v) == 0;
    eq3 = (1/Cf)*(Am*v-Rv*sqrt(abs(Ps-p2))*xv) == 0;
    % Solve for stationary points
    solution = solve([eq1,eq2,eq3],[v,p1,p2]);
    v0 = double(solution.v);
    p10 = double(solution.p1);
    p20 = double(solution.p2);
    R1 = Rv*xv/(2*sqrt(abs(p10))*Cf);
    R2 = Rv*xv/(Cf*sqrt(abs(Ps-p22)));
    K1 = Rv*sqrt(p10)/Cf;
    K2 = -Rv*sqrt(Ps-p20)/Cf;
end

% State space representation
A = [-df/m Am/m -Am/m;
    -Am/Cf R1 0;
    Am/Cf 0 R2];

B = [ 0;
    K1;
    K2];

C = [1 0 0];
D = [0];

% Create transfer function
[NUM,DEN] = ss2tf(A,B,C,D);
G = minreal(tf(NUM,DEN));
Fe = 10000;
S = [1 1];
R =  [1 0];
T = S;

P = 0.5;
% Run simulation model
A1 = Am;
A2 = Am;

%% Velocity Control Output
close all;
s = tf('s');

a = G.NUM{1}(3);
b = G.DEN{1}(2);
c = G.DEN{1}(3);
Ba1 = a;
Aa1 = s^2 + b*s +c;

%Choose values
omega = 200;
omega2 = 120;
Zeta = 1;
Zeta2 = 0.7;

% Calculates values with expressions from Maple
r0 = 2*Zeta*omega+2*Zeta2*omega2-b;
s0 = (omega^2*omega2^2)/(a);
s1 = -(-2*Zeta*omega*omega2^2-2*Zeta2*omega^2*...
    omega2+2*Zeta*c*omega+2*Zeta2*c*omega2-b*c)/a;
s2 = (4*Zeta*Zeta2*omega*omega2-2*Zeta*b*omega-2*Zeta2*...
    b*omega2+b^2+omega^2+omega2^2-c)/a;

S = s^2*s2+s*s1+s0;
R =  s*(s+r0);
t0 = omega^2/a;

T=t0*(2*Zeta2*omega2*s+omega2^2+s^2);
 %Output feedback System
Gyr=minreal((Ba1*T)/(Aa1*R+Ba1*S));
step(Gyr)

%% Cascade Position Control

Go_p = Gyr/s;
cascadeP = 2.5;
cascadeI = 0;
F_PI = cascadeP + (1/s)*cascadeI;

Gc_p = minreal((Go_p*F_PI)/(1+Go_p*F_PI));
figure
step(Gc_p)

%% Discrete Velocity Control
GyrStepInfo = stepinfo(Gyr);
Ts = GyrStepInfo.RiseTime/6;
% Ts = 0.001;
Gd = c2d(G,Ts,'zoh');
z = tf('z');
Bd = Gd.NUM{1}(2)*z + Gd.NUM{1}(3);
Ad = Gd.NUM{1}(1)*z^2 + Gd.NUM{1}(2)*z + Gd.NUM{1}(3);

SRd = c2d(S/R,Ts,'zoh');
TRd = c2d(T/R,Ts,'zoh');


Gyr_d = minreal((Gd*TRd)/(1+Gd*SRd));
step(Gyr_d)

%% Discrete Position Control
Gc_p_info = stepinfo(Gc_p);
Ts2 = Gc_p_info.RiseTime/10
Gd_p = c2d(Go_p,Ts2,'zoh');
z_p = tf('z');

F_PI_d = c2d(F_PI,Ts2,'zoh');

Gc_p_d = minreal((Gd_p*F_PI_d)/(1+Gd_p*F_PI_d));
step(Gc_p_d)



