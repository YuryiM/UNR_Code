from sklearn.linear_model import LinearRegression
import numpy as np 
import math

# Question 1 - Linear 

x = np.array([1,5.0,7,8,10])
y = np.array([8,11,14,16.5,19])
x_train = x.reshape(-1, 1)
y_train = y.reshape(-1, 1)
Reg = LinearRegression()
Reg.fit(x_train,y_train)

print("y =",round(Reg.intercept_[0],3)," + ",round(Reg.coef_[0][0],3),"x")

err = 0
for i in range(len(x)):
    err += (y[i] - Reg.intercept_[0] - Reg.coef_[0][0] * x[i])**2
print("Error:",round(err,3),"%")

# # Question 2 - Exponential

x = np.array([2,5,7,8,11,14])
y = np.array([3,11,20,45,100,250])

fit = np.polyfit(x, np.log(y), 1)
print(fit[0],fit[1])
print("y =",round(math.exp(fit[1]),3)," * e^(",round(fit[0],3),"x)")

err = 0
for i in range(len(x)):
    err += (np.log(y)[i] - fit[1] - fit[0] * x[i])**2
print("Error:",round(err,3),"%")

# # Question 3 - 

x = np.array([2,6,9,12,15,21])
y = np.array([3,11,20,45,100,250], dtype=float)
yinv = y ** -1
fit = np.polyfit(x, y ** -1, 1)

print("y = (", round(fit[1], 3), " + ",round(fit[0], 3),"x)^-1")

err = 0
for i in range(len(x)):
    err += (yinv[i] - fit[1] - fit[0] * x[i])**2
print("Error:",round(err,3),"%")