def matrix_mul(matr1,matr2):
    list_ulti = []
    leng1 = len(matr1)
    leng2 = len(matr2)
    leng2_elem = len(matr2[0])
    for i in range(leng1):
        list_to_add = []
        for a in range(leng2_elem):
            num_to_add = 0
            for b in range(leng2):
                num_to_add += matr1[i][b]*matr2[b][a]
            list_to_add.append(num_to_add)
        list_ulti.append(list_to_add)
    return list_ulti
