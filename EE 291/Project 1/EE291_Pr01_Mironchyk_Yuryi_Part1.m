% Part 1 - Function
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

disp(vpa(f(3884)))