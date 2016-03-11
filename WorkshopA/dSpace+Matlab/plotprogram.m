close all, clear all, clc
figure
subplot(1,2,1)
load('4_50amp_step.mat');
x = amp_step.X(:,1);
y1 = amp_step.Y(:,1);
y2 = amp_step.Y(:,2);

y2 = filter(ones(1,100)/100, 1, y2.Data);

%y2 = mean(y2);

plot(x.Data,y2,x.Data,y1.Data)
legend('Real','Model')
title('A: Square Wave Velocity controller Amplitude 50')
ylabel('Velocity')
xlabel('Time')
subplot(1,2,2)
load('4_50amp_volt.mat');
x = amp_volt.X(:,1);
y1 = amp_volt.Y(:,1);
% y2 = amp_volt.Y(:,2);
plot(x.Data,y1.Data)
legend('Voltage')
title('B: Voltage Velocity controller Amplitude 50')
ylabel('Voltage')
xlabel('Time')


figure
subplot(1,2,1)
load('4_10amp_sin.mat');
x = amp_sin.X(:,1);
y1 = amp_sin.Y(:,1);
y2 = amp_sin.Y(:,2);
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('A: Sine Wave Velocity controller Amplitude 10')
ylabel('Velocity')
xlabel('Time')
subplot(1,2,2)
load('4_10amp_volt.mat');
x = amp_volt.X(:,1);
y1 = amp_volt.Y(:,1);
% y2 = amp_volt.Y(:,2);
plot(x.Data,y1.Data)
legend('Voltage')
title('B: Voltage Velocity controller Amplitude 10')
ylabel('Voltage')
xlabel('Time')


figure
subplot(1,2,1)
load('4_10amp_sin_hold.mat');
x = amp_sin_hold.X(:,1);
y1 = amp_sin_hold.Y(:,1);
y2 = amp_sin_hold.Y(:,2);
plot(x.Data,y2.Data,x.Data,y1.Data)
legend('Real','Model')
title('A: Breaking Sine Wave Velocity controller Amplitude 10')
ylabel('Velocity')
xlabel('Time')
subplot(1,2,2)
load('4_10amp_volt_hold.mat');
x = amp_volt.X(:,1);
y1 = amp_volt.Y(:,1);
% y2 = amp_volt.Y(:,2);
plot(x.Data,y1.Data)
legend('Voltage')
title('B: Breaking Voltage Velocity controller Amplitude 10')
ylabel('Voltage')
xlabel('Time')