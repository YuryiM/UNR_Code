% Part 3 - Secant's Method
% Author: Yuryi Mironchyk

clc
clear

syms f(x) x

R = 8;
C1 = (5 * 10^(-6) * x * i)^(-1);
C2 = (15 * 10^(-6) * x * i)^(-1); 
L = 360 * 10^(-6) * x * i;

t1 = R + C2;
t2 = (L * t1)/(L + t1);
t3 = t2 + C1;

f(x) = abs(t3) - 50;

omega_negOne = 2000;
omega_Zero = 2050;
x(1) = omega_negOne;
x(2) = omega_Zero;

thr = 0.1;
err = 100;

i = 1;
while err > thr
    num = (f(x(end)) * (x(end) - x(end-1)));
    denom = (f(x(end)) - f(x(end-1)));
    x(end+1) = vpa(x(end) - num/denom);
    err = 100 * (abs((x(end) - x(end-1))/(x(end))));
    i = i + 1;
end

disp("Final Value:")
disp(x(end))
disp("Final Error (percent):")
disp(err)
disp("Number of Iterations:")
disp(i)