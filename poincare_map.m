function [ Y ] = poincare_map( alpha, omega, X )
% Poincare map for psi_x_x + (omega - alpha * cos(2x)) * psi - psi^3 = 0
%
fun = @(x, PSI) ([PSI(2); +(omega - alpha * cos(2*x)) * PSI(1)^3 - PSI(1)]);
[~, PSI] = ode45(fun, [0, pi], X);
Y = PSI(end, :);
end