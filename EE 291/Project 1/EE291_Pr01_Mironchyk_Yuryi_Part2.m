% Part 2 - Regula Falsi Method
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

a = 2000;
b = 8000;
x(1) = (b * f(a) - a * f(b))/(f(a) - f(b));

thr = 0.01;
err = 100;

if f(a) * f(x(end)) < 0
    b = x(end);
else
    a = x(end);
end

i = 1;
while err > thr
    x(i+1) = vpa((b * f(a) - a * f(b))/(f(a) - f(b)));
    err = 100 * abs((x(end) - x(end-1))/x(end));
    if f(a) * f(x(end)) < 0
        b = x(end);
    else
        a = x(end);
    end
    i = i + 1;
end

disp("Final Value:")
disp(x(end))
disp("Final Error (percent):")
disp(err)
disp("Number of Iterations:")
disp(i)