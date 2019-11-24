clc;
%% Variables you can change
% All lengths in cm
%Size of board
boardWidth = 100;
boardHeight = 50;

%Store position of motors
leftMotorPos = [0, boardHeight];
rightMotorPos = [boardWidth, boardHeight];

%Circumference of pulley ~ 3.8cm
pulleyCircumference = 3.8;
%One stepper motor step
stepDistance = pulleyCircumference * 1.8 / 360.0;

%Motor speeds
%Negative --> Reeling in
%Positive --> Unreeling
%leftSpeed = [0 0 0];
%rightSpeed = [-1 0 0];

%Number of steps to take and time between each step
%Divider -- Full step = 1, Half Step = 2, etc
%Negative --> CCW
%Positive --> CW
% NOTE: All 3 vectors of each side must have the same length
leftSteps = [20 0];
leftTimeSteps = [0.1 0];
leftDivider = [1 1];
%leftDividerTimes = [2];
rightSteps = [-20 100];
rightTimeSteps = [0.1 0.2];
rightDivider = [1 1];
%rightDividerTimes = [2];

%Start position
xStart = boardWidth / 2;
yStart = boardHeight / 2;
%xStart = 0;
%yStart = 0;

%Smaller timeStep for higher accuracy
timeStep = 0.01;
%times = [5 0 0];    %Must match size of speed vectors
%endTime = times(1);

%t = linspace(0, endTime, endTime / timeStep);

%% Do not change these
leftSpeed = zeros(length(leftSteps), 1);
leftTimes = zeros(length(leftSteps), 1);
rightSpeed = zeros(length(rightSteps), 1);
rightTimes = zeros(length(rightSteps), 1);
%Convert these into speeds
for i = 1:length(leftSteps)
    if leftSteps(i) == 0
        leftSpeed(i) = 0;
    elseif leftSteps(i) < 0
        leftSpeed(i) = -(leftSteps(i) * stepDistance / leftDivider(i)) / (leftSteps(i) * leftTimeSteps(i));
    else
        leftSpeed(i) = (leftSteps(i) * stepDistance / leftDivider(i)) / (leftSteps(i) * leftTimeSteps(i));
    end
    leftTimes(i) = abs(leftSteps(i) * leftTimeSteps(i));
end

for i = 1:length(rightSteps)
    if rightSteps(i) == 0
        rightSpeed(i) = 0;
    elseif rightSteps(i) < 0
        rightSpeed(i) = (rightSteps(i) * stepDistance / rightDivider(i)) / (rightSteps(i) * rightTimeSteps(i));
    else
        rightSpeed(i) = -(rightSteps(i) * stepDistance / rightDivider(i)) / (rightSteps(i) * rightTimeSteps(i));
    end
    rightTimes(i) = abs(rightSteps(i) * rightTimeSteps(i));
end

%Calculate time at end of simulation
temp = [sum(leftTimes) sum(rightTimes)];
endTime = max(temp);

leftRadius = sqrt((leftMotorPos(1) - xStart)^2 + (leftMotorPos(2) - yStart)^2);
rightRadius = sqrt((rightMotorPos(1) - xStart)^2 + (rightMotorPos(2) - yStart)^2);

%Stores position of marker at each timeStep
xResult = zeros(round(endTime / timeStep + 1), 1);
yResult = zeros(round(endTime / timeStep + 1), 1);
xResult(1) = xStart;
yResult(1) = yStart;

%Iteratively compute position of marker
i = 1;  %Index into result arrays
j = 1;  %Index for left arrays
tLeft = 0;  %Time for left motor
k = 1;  %Index for right arrays
tRight = 0; %Time for right motor
leftDone = false;
rightDone = false;
while tLeft < endTime
    %If task is done, move onto next one
    if ~leftDone
        leftRadius = leftRadius + leftSpeed(j) * timeStep;
        if tLeft > leftTimes(j)
            tLeft = 0;
            j = j + 1;
            if j > length(leftTimes)
                leftDone = true;
            end
        end
    end
    
    if ~rightDone
        rightRadius = rightRadius + rightSpeed(k) * timeStep;
        if tRight > rightTimes(k)
            tright = 0;
            k = k + 1;
            if k > length(rightTimes)
                rightDone = true;
            end
        end
    end  
    [xRoots, yRoots] = circcirc(leftMotorPos(1), leftMotorPos(2), leftRadius, rightMotorPos(1), rightMotorPos(2), rightRadius);
    xResult(i + 1) = xRoots(1);
    yResult(i + 1) = min(yRoots);
    i = i + 1;
    tLeft = tLeft + timeStep;
    tRight = tRight + timeStep;
end

%Iteratively compute position of marker
% j = 1;
% for i = 1:length(times)    
%     t = 0;  %Reset timer
%     endTime = times(i);     %Set duration at this speed setting
%     while t < endTime
%         leftRadius = leftRadius + leftSpeed(i) * timeStep;
%         rightRadius = rightRadius + rightSpeed(i) * timeStep;    
%         [xRoots, yRoots] = circcirc(leftMotorPos(1), leftMotorPos(2), leftRadius, rightMotorPos(1), rightMotorPos(2), rightRadius);
%         xResult(j + 1) = xRoots(1);
%         yResult(j + 1) = min(yRoots);
%         j = j + 1;
%         t = t + timeStep;
%     end
% end

figure(1);
plot(xResult, yResult, 'k');
hold on;
plot(leftMotorPos(1), leftMotorPos(2), 'b*');
plot(rightMotorPos(1), rightMotorPos(2), 'b*');
plot(xStart, yStart, 'r*');
plot(xResult(length(xResult)), yResult(length(yResult)), 'g*');
hold off;
xlim([-1 rightMotorPos(1) + 1]);
ylim([-1 rightMotorPos(2) + 1]);
legend('Location', 'eastoutside', 'Drawing', 'Left Motor', 'Right Motor', 'Start', 'End');
pbaspect([boardWidth boardHeight 1]);  %Adjust ratio of graph window