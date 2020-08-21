def find_if_smallest(n):
    state = True
    for a in range(n):
        if a < 2:
            continue
        if n % a == 0:
            state = False
            break
    return state

def prime_factors(n):
    list_to_return = []
    if n == 2:
        list_to_return.append(n)
    for i in range(n/2+1):
        if i <=1:
            continue
        if n % i == 0:
            if find_if_smallest(i):
                list_to_return.append(i)
    return list_to_return

