function [acceleration,velocity,position,voltFollowing,volt,err]  = Controller(feedback)
%#codegen
% PERSISTENT VARIABLES
persistent time;
if isempty(time)
    time = 0;
end

persistent oldAcc;
if isempty(oldAcc)
    oldAcc = 0;
end

persistent oldVel;
if isempty(oldVel)
    oldVel = 0;
end

persistent oldPos;
if isempty(oldPos)
    oldPos = 0;
end
%Update "time"


% Trajectory Planner Variables
Ts = 0.01;
vmax = 270;% 252;
amax = 255; %369;
amin = -amax;
rs = 10;
t1 = sqrt(rs/amax);
t2 = t1;
t3 = t1+t2;
voltmax = 24;

%Initial Value block
out1 = amax;
%%SIGNAL GENERATOR
%Reset to 0 at t1 block
out2 = 0;
if(time >= t1)
    out2 = amin;
end

%retardation at t2 block
out3 = 0;
if(time >= t2)
    out3 = amin;
end

% Reset at t3 block
out4 = 0;
if(time >= t3)
    out4 = amax;
end

acceleration = out1+out2+out3+out4;
oldAcc = acceleration;
%% INTEGRATOR PARTS
%For velocity
velocity = oldVel + Ts*(acceleration+oldAcc)/2;
oldVel = velocity;

%For position
position = oldPos + Ts*(velocity+oldVel)/2;

oldPos = position;

%% MODEL FOLLOWING PART

% Model Following variables
J1 = 6e-4;
motor_j = 7.46e-7;
n = 5;
motor_k = 0.0697;
motor_R = 112;
motor_d = 1e-5;
%% Input Acceleration Part

accPart = acceleration*(J1/(n^2)+motor_j);
 
%% Input Velocity Part
 
velPartK = velocity*motor_k;
velPartD = velocity*motor_d;
 
%%Output
 
voltFollowing = (accPart+velPartD)*motor_R/motor_k + velPartK;


%% PID CONTROLLER

% PERSISTENT VARIABLES
persistent oldErr
if isempty(oldErr)
    oldErr = 0;
end
persistent olderErr
if isempty(olderErr)
    olderErr=0;
end
persistent oldPIDVolt
if isempty(oldPIDVolt)
    oldPIDVolt = 0;
end
persistent olderPIDVolt
if isempty(olderPIDVolt)
    olderPIDVolt = 0;
end
% PID parameters
s2 = 1348;
s1 = -1899;
s0 = 692;
r0 = 0.89;

% Error
err = position - feedback;

%%PID
PIDVolt = s2*err+s1*oldErr+s0*olderErr+r0*olderPIDVolt-(r0-1)*oldPIDVolt;
olderPIDVolt = oldPIDVolt;
oldPIDVolt = PIDVolt;
olderErr = oldErr;
oldErr = err;
%% OUTPUT

volt = voltFollowing+PIDVolt;

if(volt >= voltmax)
    volt = voltmax;
elseif(volt <= -voltmax)
    volt = -voltmax;
end


time = time +Ts;

end