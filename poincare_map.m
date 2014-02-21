function [ Y ] = poincare_map( f, T, X )
% Poincare map of function f for the period T from the point X of the phase
% plane

[~, Solution] = my_ode(f, [0; T], X);
Y = Solution(end, :);

end