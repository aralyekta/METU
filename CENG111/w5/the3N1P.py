def the3N1P(n):
    calc_num = 1
    while n > 1:
        if n % 2 == 1:
            n = 3*n+1
        else:
            n = n/2
        calc_num +=1
    return calc_num

