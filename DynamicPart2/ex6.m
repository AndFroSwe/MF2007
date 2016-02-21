close all, clear all ,clc

Dc = 0.05; % Cylinder diameter m
Dp = 0.02; %Piston rod diameter m
lp = 0.7; %maximum piston stroke m
m = 100; % total moving mass kg
uf = 200; %Linear friction coeff Ns/m
Rv = 1e-4; % Flow constant
xv = -0.01; %Valve opening -1 - 1 cm;
Ps = 20e6; %Supply pressure MPA
Pt = 0 ; %Tank return pressure MPA
Fe = 10000; %External force N
poil = 1000; % Oil density kg/m^3

B = 2e9; %Bulk modulus
A1 = (Dc/2)^2*pi; %Area of piston
A2 = (Dc/2)^2*pi - (Dp/2)^2*pi;

V0 = A1*lp;
Cf = V0/B; %Compressibility Oil