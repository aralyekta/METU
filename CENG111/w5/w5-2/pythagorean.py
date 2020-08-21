def triplets(n):
    list_return = ()
    big_loop = n
    while n > 1:
        for a in range(n):
            b_sq = n ** 2 - a ** 2
            b_sqr = b_sq ** 0.5
            if type(b_sqr) in (long,int):
                list_return.append(i,b_sqr,n)
    n -= 1

