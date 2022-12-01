from sklearn.linear_model import LinearRegression
import pandas as pd 
import numpy as np
import matplotlib.pyplot as plt

# Creates 2 plots
figure, axis = plt.subplots(2)

# Import data for day 1
Data = pd.read_excel('Project 2/Solar_data.xlsx', sheet_name='Day_1') 
x = Data['Irradiance'] 
y = Data['Kw'] 
time = Data['Time'] 

# Create linear regression
x_train = np.array(x)
y_train = np.array(y)
fit = np.polyfit(x_train, y_train, 1)
def linReg(x):
    return fit[0]*x + fit[1]

# Print Linear Regression Parameters
print("y =",round(fit[0],3),"x + ",round(fit[1],3))

# Plot scatter plot for day 2 data
Data = pd.read_excel('Project 2/Solar_data.xlsx', sheet_name='Day_2')
t = Data['Time'] 
x = Data['Irradiance'] 
y = Data['Kw'] 

y2 = fit[0]*x + fit[1]
axis[0].plot(t,y2,'b')

axis[0].scatter(t,y, None, 'k')
axis[0].set_ylabel("Kw")
axis[0].set_xlabel("T")
axis[0].set_title("Day 2 Model")

# Calculate error
err = []
for i in range(len(x)):
    err.append(abs(y[i] - linReg(x[i])))
axis[1].hist(err,len(err))

# Show plots
plt.show()