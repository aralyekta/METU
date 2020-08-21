def find_range(list1):
    mino = list1[0]
    maxo = list1[0]
    for i in range(len(list1)):
        num = list1[i]
        if num > maxo:
            maxo = num
        if num < mino:
            mino = num
    return maxo-mino

def histogram(list1,num):
    list1.sort()
    list_to_return = []
    kacar_kacar = find_range(list1)/num
    for i in range(num):
        row_to_return = []
        check_if = kacar_kacar*(i+1)
        leng = len(list1)
        how_many_times = 0
        for a in range(leng):
            if list1[a] <= check_if:
                row_to_return.append(list1[a])
                how_many_times += 1
        list1 = list1[how_many_times:]
        if how_many_times == 0:
            continue
        list_to_return.append(row_to_return)
    return list_to_return

                

