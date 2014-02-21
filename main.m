%% main
clc
clear

omega = 1;
alpha = 0;
A = 0;
T = pi;

f = @(x,Y) [Y(2); (1 + alpha*cos(2*x))*Y(1)^3 - (omega - A*cos(2*x))*Y(1)];  

% grid on the phase plane
m = 50;
n = 25;
x = linspace(0, 3*sqrt(omega), n);
y = linspace(-3*sqrt(omega), 3*sqrt(omega), m);

M = zeros(m,n);
Y = zeros(2,1);

tic
parfor i = 1:m
    for j = 1:n
        Y = poincare_map(f,T,[x(j); y(i)]);
        if abs(Y(1)) < 10^5
            M(i,j) = 1;
        else
            M(i,j) = 0;
        end
    end
end
time = toc;

% I = 100*[rot90(M,2) M];
% image(I);

