def factorial(n):
    a = 1
    for i in range(n+1):
        if i == 0:
            continue
        a = a * i
    return a
