from sklearn.linear_model import LinearRegression
import pandas as pd 
import numpy as np
import matplotlib.pyplot as plt

# TODO:
# Add axes labels

# Creates 2 plots
figure, axis = plt.subplots(2)

# Import data for day 1
Data = pd.read_excel('Project 2/Solar_data.xlsx', sheet_name='Day_1') 
x = Data['Irradiance'] 
y = Data['Kw'] 
time = Data['Time'] 

# Create linear regression
x_train = np.array(x).reshape(-1, 1)
y_train = np.array(y).reshape(-1, 1)
Reg = LinearRegression()
Reg.fit(x_train,y_train)
def linReg(x):
    return Reg.intercept_[0] + Reg.coef_[0][0]*x

# Print Linear Regression Parameters
print("y =",round(Reg.intercept_[0],3)," + ",round(Reg.coef_[0][0],3),"x")

# Plot linear regression
xr = np.linspace(0,1,100)
yr = Reg.intercept_[0] + Reg.coef_[0][0]*xr
axis[0].plot(xr,yr,'r')

# Plot scatter plot for day 2 data
Data = pd.read_excel('Project 2/Solar_data.xlsx', sheet_name='Day_2') 
x = Data['Irradiance'] 
y = Data['Kw'] 
time = Data['Time']
axis[0].scatter(x,y, None, 'k')
axis[0].set_ylabel("Irradiance")
axis[0].set_xlabel("Kw")
axis[0].set_title("Day 2 Model")

# Calculate error
err = []
for i in range(len(x)):
    err.append(abs(y[i] - linReg(x[i])))
axis[1].hist(err,len(err))

# Show plots
plt.show()
