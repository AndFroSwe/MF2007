%% Hydraulic cylinder
% Velocity controller for hydraulic system
% TODO: Verify that model works in both directions
% TODO: Design position controller in outer loop (cascaded)
% TODO: Make discrete time approximation
% TODO: Find longest sampling time
close all, clear all, clc
%%
% Piston parameters
Dc = 0.05; % Cylinder diameter m
Dp = 0.02; %Piston rod diameter m
lp = 0.7; %maximum piston stroke m
m = 100; % total moving mass kg
uf = 200; %Linear friction coeff Ns/m
Rv = 1e-4; % Flow constant
xv = 0.01; %Valve opening -1 - 1 cm;
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
    R2 = Rv*xv/(Cf*sqrt(abs(Ps-p20)));
    K1 = Rv*sqrt(p10)/Cf;
    K2 = -Rv*sqrt(Ps-p20)/Cf;
end

% State space representation
A = [-df/m Am/m -Am/m;
    -Am/Cf R1 0;
    Am/Cf 0 R2];

B = [ 0 -1/m;
    K1 0;
    K2 0];

C = [1 0 0; 0 1 0; 0 0 1];
D = [0 0; 0 0; 0 0];
sys = ss(A,B,C,D);
% Create transfer function
[NUM,DEN] = ss2tf(A,B,C,D,1);
Fe = 10000;


P = 0.5;
% Run simulation model
A1 = Am;
A2 = Am;
sim('hydraulic_ex3.slx')
figure
plot(sim_p1)
hold on
grid on
plot(sim_p2)
p1lin = sim_linear.Data(:,2)+p10;
p2lin = sim_linear.Data(:,3)+p20;

plot(sim_linear.Time,p1lin)
plot(sim_linear.Time,p2lin)
legend('P1sim','P2sim','P1lin','P2lin')
figure
plot(sim_velocity)
hold on
plot(sim_linear.Time,sim_linear.Data(:,1))
legend('Velocity simulated','Velocity Linear')


%% 
C1 = [1 0 0; 0 0 0; 0 0 0];
[NUM,DEN] = ss2tf(A,B,C1,D,1);
NUM = NUM(1,:);
tf_lin = tf(NUM,DEN);



