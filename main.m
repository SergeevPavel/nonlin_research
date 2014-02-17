omega = 1;
alpha = -1;

tic
n = 200;
m = 400;
M = zeros(m, n);
stepx = 0.01;
stepy = 0.01;
parfor i = 1:m
    warning off
    for j = 1:n
        Y = poincare_map(alpha, omega, [(j - 1) * stepx, -2 + (i - 1) * stepy]);
        if abs(Y(1)) < 10^13
            M(i, j) = 1;
        else
            M(i, j) = 0;
        end
    end
end
toc