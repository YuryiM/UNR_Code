from sklearn.linear_model import LinearRegression
import pandas as pd 
import numpy as np
import matplotlib.pyplot as plt

figure, axis = plt.subplots(4)

# Import data for day 1
Data = pd.read_excel('Project 2/Solar_data.xlsx', sheet_name='Day_1') 
x = Data['Irradiance'] 
y = Data['Kw'] 
time = Data['Time'] 
axis[3].scatter(x,y, None, 'k')
axis[3].set_ylabel("Irradiance")
axis[3].set_xlabel("Kw")
axis[3].set_title("Day 1 Model")
axis[3].legend(loc="upper left")

# Create poly 3 regression
x_train1 = np.array(x)
y_train1 = np.array(y)
fit1 = np.polyfit(x_train1, y_train1, 3)
print("y =", round(fit1[0],3),"x^3 +", round(fit1[1],3),"x^2 +", round(fit1[2],3),"x +", round(fit1[3],3))
def poly3Reg(x):
    return fit1[0] * pow(x,3) + fit1[1] * pow(x,2) + fit1[2] * x + fit1[3]

# Plot poly 3 regression
xr = np.linspace(0,1,100)
yr = fit1[0] * pow(xr,3) + fit1[1] * pow(xr,2) + fit1[2] * xr + fit1[3]
axis[0].plot(xr,yr,'r', label="poly 3")
axis[3].plot(xr,yr,'r', label="poly 3")


# Create poly 5 regression
x_train2 = np.array(x)
y_train2 = np.array(y)
fit2 = np.polyfit(x_train2, y_train2, 5)
print("y =", round(fit2[0],3),"x^5 +", round(fit2[1],3),"x^4 +", round(fit2[2],3),"x^3 +", round(fit2[3],3),"x^2 +", round(fit2[4],3),"x +", round(fit2[5],3))
def poly5Reg(x):
    return fit2[0] * pow(x,5) +fit2[1] * pow(x,4) +fit2[2] * pow(x,3) + fit2[3] * pow(x,2) + fit2[4] * x + fit2[5]

# Plot poly 5 regression
xr = np.linspace(0,1,100)
yr = fit2[0] * pow(xr,5) +fit2[1] * pow(xr,4) +fit2[2] * pow(xr,3) + fit2[3] * pow(xr,2) + fit2[4] * xr + fit2[5]
axis[0].plot(xr,yr,'b', label="poly 5")
axis[3].plot(xr,yr,'b', label="poly 5")



# Plot scatter plot for day 2 data
Data = pd.read_excel('Project 2/Solar_data.xlsx', sheet_name='Day_2') 
x = Data['Irradiance'] 
y = Data['Kw'] 
time = Data['Time']
axis[0].scatter(x,y, None, 'k')
axis[0].set_ylabel("Irradiance")
axis[0].set_xlabel("Kw")
axis[0].set_title("Day 2 Model")
axis[0].legend(loc="upper left")

# Calculate error for poly3 and poly5
err3 = []
err5 = []
for i in range(len(x)):
    err3.append(abs(y[i] - poly3Reg(x[i])))
    err5.append(abs(y[i] - poly5Reg(x[i])))
axis[1].hist(err3,len(err3))
axis[2].hist(err5,len(err5))
axis[1].set_title("3 Deg Poly Error")
axis[2].set_title("5 Deg Poly Error")

# Show plots
plt.show()
