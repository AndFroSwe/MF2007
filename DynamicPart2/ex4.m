clear all, close all, clc;
warning('off', 'all')
%% Define parameters
n = 5; %Gearbox ratio
J1 = 1.8e-5; %Load inertia 1
J2 = 1.8e-5; %Load inertia 2
Vmax = 1; %Supply voltage
Vmin = -24; %Supply voltage
Imax = 430e-3; %Maximum current
V_i = Vmax;
V_w = Vmax;
sim_V = Vmax;
% Set up generic simulation parameters, change when using sine input or
% karnop
F_c = 0.001;
d_v = 1;
enable_sin = 0;
enable_karnop = 0;
sim_sin_amp = 1;
sim_sin_freq = 1;
sim_quantization_interval = 0;
sim_zoh_sample_time = 0;
% Motor parameters
motor_pars = struct(); % Create empty struct for motor
motor_pars.R = 112; % Terminal resistance [Ohm]
motor_pars.L = 11.4e-3;    % Terminal inductance [H]
motor_pars.d = 3.8e-6; %Viscous friction in brushes
motor_pars.k = 69.7e-3;    % Torque constant [Nm/A]
motor_pars.J_m = 7.46e-7;  % Rotor inertia

motor_L = motor_pars
motor = motor_pars
J = J1+J2
%% part 4: Quantizing
% Set parameters
enable_sin = 0;     % Set 1 to enable sine input
enable_karnop = 0;  % Dont use karnop
zoh_sample_time = 1;   % Sample time in zoh [ms]
    % Simulate
    simtime = 1; % Sim for 1 s
    sim_step_v = 10;


for enc = [512 8192]
    sim('ex2_sim.slx')
    for i = 1:3
        
        % Calculated parameters
        sim_quantization_interval = 2*pi/enc;    % Ppr to degrees
        sim_zoh_sample_time = 1*10^-i;  % Sample time, from ms to s

        sim('ex4_sim.slx')
        % Plot of unquantized signal
        even = [2 4 6];
        pos = even(i);
       
        if enc == 512
            uneven = [1 3 5];
            pos = uneven(i);
        end
        
        subplot(3,2,pos)
        plot(sim_ex2_v_w)
        title_string = sprintf('Encoder: %1.0f, Sampling time: %0.3f' ,...
        enc,sim_zoh_sample_time);
        title(title_string)
        hold on
        stairs(ex4_sim_v_disc.Time, ex4_sim_v_disc.Data, 'r')
        
    end
end
% 
% grid on
% title('Motor control with and without quantization')
% xlabel('Time [s]')
% ylabel('\omega [rad/s]')
% legend('Unquantized velocity', '1e-3 Sample Time')
