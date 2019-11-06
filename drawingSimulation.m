clear all;
clc;

%Size of board
boardWidth = 10;
boardHeight = 10;

%Store position of motors
leftMotorPos = [0, 10];
rightMotorPos = [10, 10];

%Motor speeds
%Negative --> Reeling in
%Positive --> Unreeling
leftSpeed = [0 0 0];
rightSpeed = [-1 0 0];

%Smaller timeStep for higher accuracy
timeStep = 0.01;
times = [5 0 0];    %Must match size of speed vectors
endTime = times(1);
t = 0;
%t = linspace(0, endTime, endTime / timeStep);

%Start position
xStart = boardWidth / 2;
yStart = boardHeight / 2;
xStart = 0;
yStart = 0;
leftRadius = sqrt((leftMotorPos(1) - xStart)^2 + (leftMotorPos(2) - yStart)^2);
rightRadius = sqrt((rightMotorPos(1) - xStart)^2 + (rightMotorPos(2) - yStart)^2);

%Stores position of marker at each timeStep
xResult = zeros(round(sum(times) / timeStep + 1), 1);
yResult = zeros(round(sum(times) / timeStep + 1), 1);
xResult(1) = xStart;
yResult(1) = yStart;

%Iteratively compute position of marker
j = 1;
for i = 1:length(times)    
    t = 0;  %Reset timer
    endTime = times(i);     %Set duration at this speed setting
    while t < endTime
        leftRadius = leftRadius + leftSpeed(i) * timeStep;
        rightRadius = rightRadius + rightSpeed(i) * timeStep;    
        [xRoots, yRoots] = circcirc(leftMotorPos(1), leftMotorPos(2), leftRadius, rightMotorPos(1), rightMotorPos(2), rightRadius);
        xResult(j + 1) = xRoots(1);
        yResult(j + 1) = min(yRoots);
        j = j + 1;
        t = t + timeStep;
    end
end

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
pbaspect([1 1 1]);  %Output square graph