from math import exp, factorial

def fact(k):
    if k <= 1:
        return 1
    else:
        return k*fact(k-1)

def combi(k, n):
    prod = 1
    for i in range(n-k+1, n+1):
        prod *= i
    return prod / fact(k)
    
def bn(k, p):
    s = 0
    for i in range(0, k):
        s += p(i)
    return s

def p(k): # x = k 
    return (0.001)**k * (0.999)**(1000-k) * combi(k, 1000)


def p2(k):
    return exp(-1) * (1 / factorial(k))

for a in range(0, 6):
    print(a, bn(a, p))
