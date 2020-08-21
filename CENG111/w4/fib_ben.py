def fib_series(n, pre=1, cur=1):
    if n <=1:
        return [pre]
    else:
        return [pre] + fib_series(n-1,cur,pre+cur)

