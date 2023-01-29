# 1. Power Method

# Tested, absolutely works

import numpy as np
from numpy.linalg import inv

row = -1
x = np.array([1, 1, 1])
a = np.array([[2, 0, 1], 
              [3, 6, -2],
              [5, -1, -2]])
              
for i in range(5):
    print("===================================")
    print("Iteration",i+1)
    x = np.dot(a, x)
    print("X:",x)
    if i > 0:
        lambda_1, x = x[row], x / x[row]
    else:
        row = int(np.where(np.absolute(x) == np.absolute(x).max())[0])
        lambda_1, x = x[row], x / x[row]
    print("New eigenvector:",x)
    print("New eigenvalue:",lambda_1)
    if i != 0:
        err = 100 * abs((lambda_1 - oldLambda)/lambda_1)
        print("Error:",err,"%")
        oldLambda = lambda_1
    else:
        oldLambda = lambda_1

print("Smallest eigenvalue of A:",(oldLambda))

# 2. Inverse Power Method
row = -1
x = np.array([1, 1, 1])
a = inv(np.array([[8, 0, 2], 
              [1, 6, -2],
              [7, -1, -2]]))
              
for i in range(5):
    print("===================================")
    print("Iteration",i+1)
    x = np.dot(a, x)
    print("X:",x)
    if i > 0:
        lambda_1, x = x[row], x / x[row]
    else:
        row = int(np.where(np.absolute(x) == np.absolute(x).max())[0])
        lambda_1, x = x[row], x / x[row]
    print("New eigenvector:",x)
    print("New eigenvalue:",lambda_1)
    if i != 0:
        err = 100 * abs((lambda_1 - oldLambda)/lambda_1)
        print("Error:",err,"%")
        oldLambda = lambda_1
    else:
        oldLambda = lambda_1
print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")    
print("Smallest eigenvalue of A:",(oldLambda)**(-1))
print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")