def triplets(n):
    list_return = []
    while n >= 5:
        for i in range(1,n-1):
            b_kare = (n-1)**2 - i** 2
            b = b_kare ** 0.5
            if int(b) == b and b != 0:
                tuple_to_add = [i,int(b),n-1]
                tuple_to_add.sort()
                if tuple_to_add not in list_return:
                    list_return.append((tuple_to_add))
        n -= 1

    leng = len(list_return)
    return list_return
