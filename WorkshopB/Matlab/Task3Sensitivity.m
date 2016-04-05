close all, clear all, clc;

s = tf('s');
a = 25.15;
b = 2.157;
c = 0.5107;
d = 1.988;
omega1 = 10;
omega2 = 5;

A = s+b;
B = a;
R = s;
S = c*s+d;
Am = s+omega1;
Ao = s+omega2;
t0 = 0.3976;
T = t0*Ao;

Go = B/A;
Gff = T/R;
Gfb = S/R;

%% Complementary sensitivity function

Se = (A*R)/(Am*Ao)
Te = (B*S)/(Am*Ao)

figure(19834735)
bode(Se)
hold on
bode(Te)

title('Sensitivity functions')
legend('Se', 'Te');

%% Faster poles

omega2 = 5*omega1

Am = s+omega1;
Ao = s+omega2;
Se = (A*R)/(Am*Ao)
Te = (B*S)/(Am*Ao)

figure(19834736)
bode(Se)
hold on
bode(Te)

title('Sensitivity functions')
legend('Se', 'Te');

