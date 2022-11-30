% clear workspace 
clear 
clc
close all

%Import xls file for data visualization
A = readmatrix('test.csv');
B = readmatrix('totalDms.csv');

% Plot error vs dt
figure(1)
surf(A')
xlabel('age')
ylabel('time')
zlabel('amount')

title('plot model')

t = 0:1:101;
figure(2)
plot(t,B)
ylabel('total population')
xlabel('time')

figure(3)
plot(A(1,:))
hold on;
plot(A(10,:))
hold on;
plot(A(20,:))
hold on;
plot(A(30,:))
hold on;
plot(A(40,:))


