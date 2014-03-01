%%
clc;
clear;
close all;
addpath('cpp/Solver/');

%%
M = dlmread('output.txt');
I = 100*[rot90(M,2) M];
image(I);

%% New Plotter
xstep = 1.5 / 500;
ystep = 12 / 1000;

M = dlmread('output.txt');
I = 100*[rot90(M,2) M];

x = linspace(-1.5,1.5,1000);
y = linspace(-6,6,1000);

figure
[X,Y] = meshgrid(x,y);
contourf(X,Y,I,[1,1]);
colormap('gray');