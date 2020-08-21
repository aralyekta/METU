def lis(list1):

    leng = len(list1)
    for i in range(leng-1):
        if list1[i] <=list1[i+1]:
            a += 1
    return a
