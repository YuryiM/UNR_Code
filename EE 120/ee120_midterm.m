% For loop to iterate through the values of Ra
for Ra = 5:14
    % Set the value of the equivalent resistance
    Re = 4;
    % Calculate the value of Rb based on Ra, using the parallel resistance formula
    Rb = ((1/Re) - (1/Ra))^(-1);
    % Display the value of Ra and Rb
    disp(['Ra is ' num2str(Ra) ' and Rb is ' num2str(Rb)]);
end