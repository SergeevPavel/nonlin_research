%%
clc;
clear;
close all;
addpath('cpp/Solver/');

%%
M = dlmread('output.txt');
I = 100*[rot90(M,2) M];
image(I);