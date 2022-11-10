# Question 1

# x = [1,3,5,8,12]
# y = [20,28,None,35,41]

x = [10,13,17,19,22]
y = [20,28,None,35,41]
m = 2

# Linear

L = []
for i in range(0, 2):
    for j in range(0, 2):
        if i != j:
            Li = (x[m] - x[j])/(x[i] - x[j])
            L.append(Li)

sum = 0
for i in range(0,2):
    sum +=  L[i] * y[i]
print(sum)

# Quadratic
L = []
for i in range(0, 4):
    if i != m:
        product = 1
        for j in range(0, 4):
            if i != j and j != m:
                product *= (x[m] - x[j])/(x[i] - x[j])
        print(product)
        L.append(product)
L.insert(2, None)
sum = 0
for i in range(0,4):
    if i != 2:
        sum +=  L[i] * y[i]
print(sum)

# Cubic

L = []
for i in range(0, 5):
    if i != m:
        product = 1
        for j in range(0, 5):
            if i != j and j != m:
                product *= (x[m] - x[j])/(x[i] - x[j])
        print(product)
        L.append(product)
L.insert(2, None)
sum = 0
for i in range(0,5):
    if i != 2:
        sum +=  L[i] * y[i]
print(sum)


# Question 2