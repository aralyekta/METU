def find3N1P(n):
    a = 1
    while n != 1:
        if n % 2 == 1:
            n = 3*n+1
        else:
            n = n/2
        a += 1
    return a

def max3N1P(n):
    max_index = 1
    max_3N1P = 1
    for i in range(n+1):
        if i <= 1:
            continue
        second_3N1P = find3N1P(i)
        if second_3N1P > max_3N1P:
            max_3N1P = second_3N1P
            max_index = i
    return (max_index,max_3N1P)
