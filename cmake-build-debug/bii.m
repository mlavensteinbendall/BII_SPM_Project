% clear workspace 
clear 
clc
close all

load('Survival_Rate.mat')
load('inverse_problem_modelD_withoutBeta_group1.mat');
%Import xls file for data visualization
A = readmatrix('solution.csv');
B = readmatrix('totalDms.csv');

% A = readmatrix('solution-b=8:3.csv');
% B = readmatrix('totalDms-b=8:3.csv');
% C = readmatrix('solution-b=16:3.csv');
% D = readmatrix('totalDms-b=16:3.csv');
% E = readmatrix('solution-b=32:3.csv');
% F = readmatrix('totalDms-b=32:3.csv');


% PLOT SURFACE AND TOTAL POPULATION IN ONE FIGURE
figure(1)

% Plot surface ------------------------------------
subplot(1,2,1)
% subplot(3,2,1)    % use if plotting multiple rows
mesh(A)             
xlabel('Age (days)')
ylabel('Time (days)')
zlabel('Population')
title('Structured Population Model with b = 8/3')

% Define time interval ----------------------------
t = 0:1:102;

% Plot total population over time -----------------
subplot(1,2,2)
% subplot(3,2,2)    % use if plotting multiple rows
plot(t,B,'k')       % plot total pop from model
hold on;
plot(times,total_population, 'ok') % plot experimental data
ylabel('Population')
xlabel('time (days)')
title('Total Population with b = 8/3')


% Used for plotting for comparison of b
% subplot(3,2,3)
% mesh(C)
% xlabel('Age (days)')
% ylabel('Time (days)')
% zlabel('Population')
% title('Structured Population Model with b = 16/3')
% 
% t = 0:1:101;
% subplot(3,2,4)
% plot(t,D,'k')
% hold on;
% plot(times,total_population, 'ok')
% ylabel('Population')
% xlabel('time (days)')
% title('Total Population with b = 16/3')
% % legend('model','experiment')
% 
% 
% subplot(3,2,5)
% mesh(E)
% xlabel('Age (days)')
% ylabel('Time (days)')
% zlabel('Population')
% title('Structured Population Model with b = 32/3')
% 
% 
% subplot(3,2,6)
% plot(t,F, 'k')
% hold on;
% plot(times,total_population, 'ok')
% ylabel('Population')
% xlabel('time (days)')
% title('Total Population with b = 32/3')


% PLOT THE MORTALITY RATE AT EACH AGE ------------
figure(2)

plot(SplineFunction, 'or')
xlabel('Age (days)');
ylabel('Mortality Rate (% of individuals)')
title('Mortality Rate at Each Age')


% %MAKE VIDEO ------------------------------------
% C = A';
% a = 0:1:90;
%
% figure(3) 
% axis tight manual
% v = VideoWriter('popTime.avi');
% 
% v.FrameRate = 10;
% 
% set(gca,'nextplot','replacechildren'); 
% 
% open(v);
% for i = 1:103
%     plot(a,C(:,i))
%     xlim([0,91]);
%     ylim([0,60]);
%     
%     ylabel('Population')
%     xlabel('Age (days)')
%     title(sprintf('Age Distribution over Time (t = %d)',i-1))
%     
%     F = getframe(gcf);
%     frame = getframe(gcf);
%     writeVideo(v,frame);
% end
% 
% close(v);

