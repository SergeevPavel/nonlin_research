function [ T, Y ] = my_ode( ode, tspan, y0 )

h = 0.02;
n = length(y0);
N = floor((tspan(2) - tspan(1)) / h) + 1;
T = linspace(tspan(1),tspan(2),N)';

Y = zeros(N,n);
k = zeros(4,n);

Y(1,:) = y0;
for i = 1:(N-1)
	k(1,:) = h*ode(T(i), Y(i,:));
	k(2,:) = h*ode(T(i) + h/2, Y(i,:) + 1/2 * k(1,:));
	k(3,:) = h*ode(T(i) + h/2, Y(i,:) + 1/2 * k(2,:));
	k(4,:) = h*ode(T(i) + h, Y(i,:) + k(3,:));
	Y(i+1,:) = Y(i,:) + (1/6)*(k(1,:) + 2*k(2,:) + 2*k(3,:) + k(4,:));
end

end

