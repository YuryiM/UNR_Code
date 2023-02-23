I = [1 + 0i; 0; 0; 1.732 + 1i];
Ir = [1;0;0;2];
Itheta = [0;0;0;30];



Y = [1 -1 0 0;
    -1 (2.083-1i) (-0.3333+1i) -0.25;
     0 (-0.3333+1i) (0.3333 - 0.25i) -0.25i;
     0 -0.25 -0.25i (0.25 - 0.08333i)];


V = Y\I;
disp(V);

Va = real(V);
Vb = imag(V);

[Vtheta, Vrho] = cart2pol(Va, Vb);

Vtheta = Vtheta * (180/pi);

disp("Name: Yuryi Mironchyk");

disp("Input data:");
disp(Y);
disp("*");
disp("[V10 ; V20 ; V30 ; V40]");
disp("=");
disp(I);
% disp()

disp("Input admittance matrix, Y:");
disp(Y);

disp("Current Vector in Polar Form (deg):")
disp("r = ");
disp(Ir);
disp("theta = ");
disp(Itheta);

disp("Voltage Vector in Polar Form (deg):");
disp("r = ");
disp(Vrho);
disp("theta = ");
disp(Vtheta);