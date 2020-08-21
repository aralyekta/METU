def isprime(n):
    a = 2
    state = True
    if n == 2:
        return state
"""    for i in range(n):
        if i < 2:
            continue
        if n % i == 0:
            state = False
        else:
            continue
"""

    while a < n:
        if n % a != 0:
            continue
        else:
            state = False
        a += 1
    return state
