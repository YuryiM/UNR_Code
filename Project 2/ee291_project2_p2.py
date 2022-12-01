from sklearn.linear_model import LinearRegression
import pandas as pd 
import numpy as np
import matplotlib.pyplot as plt

# Create 3 plots
figure, axis = plt.subplots(3)

# Import data for day 1
Data = pd.read_excel('Project 2/Solar_data.xlsx', sheet_name='Day_1') 
x = Data['Irradiance'] 
y = Data['Kw'] 
time = Data['Time'] 

# Create poly 3 regression
x_train = np.array(x)
y_train = np.array(y)
fit1 = np.polyfit(x_train, y_train, 3)
print("y =", round(fit1[0],3),"x^3 +", round(fit1[1],3),"x^2 +", round(fit1[2],3),"x +", round(fit1[3],3))
def poly3Reg(x):
    return fit1[0] * pow(x,3) + fit1[1] * pow(x,2) + fit1[2] * x + fit1[3]

# Create poly 5 regression
fit2 = np.polyfit(x_train, y_train, 5)
print("y =", round(fit2[0],3),"x^5 +", round(fit2[1],3),"x^4 +", round(fit2[2],3),"x^3 +", round(fit2[3],3),"x^2 +", round(fit2[4],3),"x +", round(fit2[5],3))
def poly5Reg(x):
    return fit2[0] * pow(x,5) +fit2[1] * pow(x,4) +fit2[2] * pow(x,3) + fit2[3] * pow(x,2) + fit2[4] * x + fit2[5]

# Plot scatter plot for day 2 data
Data = pd.read_excel('Project 2/Solar_data.xlsx', sheet_name='Day_2') 
t = Data['Time'] 
x = Data['Irradiance'] 
y = Data['Kw'] 
time = Data['Time']

# Create the poly3 and the poly5 graphs
y3 = fit1[0] * pow(x,3) + fit1[1] * pow(x,2) + fit1[2] * x + fit1[3]
y5 = fit2[0] * pow(x,5) +fit2[1] * pow(x,4) +fit2[2] * pow(x,3) + fit2[3] * pow(x,2) + fit2[4] * x + fit2[5]

# Plot the poly3 graph
axis[0].plot(t,y3,'r', label="poly3")
# Plot the poly5 graph
axis[0].plot(t,y5,'b', label="poly5")

# Plot the day 2 data points
axis[0].scatter(t,y, None, 'k')
axis[0].set_ylabel("Kw")
axis[0].set_xlabel("T")
axis[0].set_title("Day 2 Model")
axis[0].legend(loc="upper left")

# Calculate error for poly3 and poly5
err3 = []
err5 = []

# Calculate square error for poly3 and poly5
poly3_msq = 0
poly5_msq = 0

for i in range(len(t)):
    err3.append(abs(y[i] - poly3Reg(x[i])))
    poly3_msq += abs(y[i] - poly3Reg(x[i]))**2

    err5.append(abs(y[i] - poly5Reg(x[i])))
    poly5_msq += abs(y[i] - poly5Reg(x[i]))**2

print("3rd Degree Total Squared Error: ", poly3_msq)
print("5th Degree Total Squared Error: ", poly5_msq)

# Create histogram of errors
axis[1].hist(err3,int(len(err3)/5))
axis[2].hist(err5,int(len(err5)/5))

axis[1].set_title("3 Deg Poly Error")
axis[2].set_title("5 Deg Poly Error")    

# Show plots
plt.show()