def find_if_perfect(n):
    a = 0
    for i in range(1,n/2+1):
        if n % i == 0:
            a += i
        else:
            continue
    if a == n:
        return (0,n)
    elif a > n:
        return (1,n)
    elif a < n:
        return (2,n)

def perfect_numbers(n):
    list0 = []
    list1 = []
    list2 = []
    for i in range(1,n):
        tuplo = find_if_perfect(i)
        if tuplo[0] == 0:
            list0.append(i)
        elif tuplo[0] == 1:
            list1.append(i)
        elif tuplo[0] == 2:
            list2.append(i)
    return (list0,list1,list2)

