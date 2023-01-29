# Question 1
# x = [[2,1,3]]
# def x1(x2,x3):
#     return (30 + 2*x2 + 5*x3)/10
# def x2(x1,x3):
#     return (-5 + 2*x1 + 5 * x3)/15
# def x3(x1,x2):
#     return (25 + 5*x1 + 5 * x2)/14
# def err(iter,xval):
#     return round(100*abs(x[iter-1][xval]-x[iter][xval])/x[iter][xval],2)
# for i in range(1, 5):
#     print("-----------------------------")
#     print("Iteration",i)
#     xi = [
#         x1(x[i-1][1],x[i-1][2]),
#         x2(x[i-1][0],x[i-1][2]),
#         x3(x[i-1][0],x[i-1][1]),
#         ]
#     x.append(xi)
#     print("New x values:")
#     print("x1",round(x[i][0],3))
#     print("x2",round(x[i][1],3))
#     print("x3",round(x[i][2],3))
#     print("Iteration",i,"Errors:")
#     print("x1:",err(i,0),"%")
#     print("x2:",err(i,1),"%")
#     print("x3:",err(i,2),"%")
x = 1
R = 2
C1 = 3
C2 = 4
L = 5
y = ( (x * R^2 * L) + ( L/C2 )*( x*L - ( 1/(x*C2) ) ) ) / ( R^2 + (x*L - (1/(x*C2))) )^2

print(y)

# Question 2
# x = [[2,1,1,2]]
# def x1(x2,x3,x4):
#     return (15 + 4*x2 + 2 * x3 + 3 * x4)/13
# def x2(x1,x3,x4):
#     return (10 + 4 * x1 + 3 * x3 + 3 * x4)/20
# def x3(x1,x2,x4):
#     return (12 + 2 * x1 + 3 * x2 + x4)/9
# def x4(x1,x2,x3):
#     return (-8 + 3 * x1 + 3 * x2 + x3)/13
# def err(iter,xval):
#     return round(100*abs(x[iter-1][xval]-x[iter][xval])/x[iter][xval],2)
# for i in range(1, 5):
#     print("=============================")
#     print("Iteration",i)
#     print("=============================")
#     x.append([
#         x1(x[i-1][1],x[i-1][2],x[i-1][3]),
#         x2(x[i-1][0],x[i-1][2],x[i-1][3]),
#         x3(x[i-1][0],x[i-1][1],x[i-1][3]),
#         x4(x[i-1][0],x[i-1][1],x[i-1][2])
#         ])
#     for j in range(0, 4):
#         print("New value:")
#         print("x"+str(j+1)+" = "+str(round(x[i][j],3)))
#         print("Error:")
#         print("x" + str(j+1)+": ",err(i,j),"%")
#         print("-----------------")
    # print("x2",round(x[i][1],3))
    # print("x3",round(x[i][2],3))
    # print("x4",round(x[i][3],3))
    # print("Iteration",i,"Errors:")
    
    # print("x2:",err(i,1),"%")
    # print("x3:",err(i,2),"%")
    # print("x4:",err(i,3),"%")

