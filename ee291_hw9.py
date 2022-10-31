from sklearn.linear_model import LinearRegression
import numpy as np 
import math

# Question 1 - Linear 

x =np.array([1,5.0,7,8,10])
y =np.array([8,11,14,16.5,19])
x_train = x.reshape(-1, 1)
y_train = y.reshape(-1, 1)
Reg = LinearRegression()
Reg.fit(x_train,y_train)

print("y =",Reg.intercept_," + ",Reg.coef_,"x")

# Question 2 - Exponential

x = np.array([2,5,7,8,11,14])
y = np.array([3,11,20,45,100,250])

fit = np.polyfit(x, np.log(y), 1)

print("y =",round(math.exp(fit[0]),3)," + ",round(math.exp(fit[1]),3),"^x")

