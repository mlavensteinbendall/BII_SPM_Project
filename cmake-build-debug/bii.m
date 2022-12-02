% clear workspace 
clear 
clc
close all

%Import xls file for data visualization
A = readmatrix('solution.csv');
B = readmatrix('totalDms.csv');
C = readmatrix('test.csv');
b = xlsread('totalDMs1.xls');


% Plot error vs dt
figure(1)
surf(A')
xlabel('time')
ylabel('age')
zlabel('amount')

title('Population of Daphnia maga')

t = 0:1:102;
figure(2)
plot(t,B)
ylabel('# of individuals')
xlabel('time')
title('Total Population of Daphnia maga over time')


% Plot error vs dt
figure(3)
surf(A')
xlabel('age')
ylabel('time')
zlabel('amount')
title('C model')

figure(4)
t = 0:1:101;
plot(t,b)
ylabel('total population')
xlabel('time')

% figure(3)
% plot(A(1,:))
% hold on;
% plot(A(10,:))
% hold on;
% plot(A(20,:))
% hold on;
% plot(A(30,:))
% hold on;
% plot(A(40,:))


