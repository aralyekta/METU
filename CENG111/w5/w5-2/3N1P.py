def the3N1P(n):
    a = 1
    while (n != 1):
        if n % 2 == 1:
            n = 3*n+1
        elif n % 2 == 0:
            n = n/2
        a = a+1
    return a
