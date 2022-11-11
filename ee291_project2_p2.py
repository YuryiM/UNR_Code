from sklearn.linear_model import LinearRegression
import pandas as pd 
import numpy as np
import matplotlib.pyplot as plt

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
print("y =",round(Reg.intercept_[0],3)," + ",round(Reg.coef_[0][0],3),"x")

# Plot linear regression
xr = np.linspace(0,1,100)
yr = Reg.intercept_[0] + Reg.coef_[0][0]*xr
axis[0].plot(xr,yr,'r')

# Calculate error
err = []
for i in range(len(x)):
    err.append((y[i] - Reg.intercept_[0] - Reg.coef_[0][0] * x[i])**2)
print("Error:",err)
axis[1].hist(err,len(err))

# Plot scatter plot for day 2 data
Data = pd.read_excel('Project 2/Solar_data.xlsx', sheet_name='Day_2') 
x = Data['Irradiance'] 
y = Data['Kw'] 
time = Data['Time']
axis[0].scatter(x,y, None, 'k')

# Show plots
plt.show()
