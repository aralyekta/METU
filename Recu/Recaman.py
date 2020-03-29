def recaman(n,listo=[]):
    if n == 0:
        return [0]
    func_previous = recaman(n-1,)
    minus = func_previous[-1]-n
    plus = func_previous[-1]+n
    if minus > 0 and minus not in func_previous:
        func_previous.append(minus)
        return func_previous
    else:
        func_previous.append(plus)
        return func_previous

recaman(6)