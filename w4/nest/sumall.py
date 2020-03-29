def sum_all(listo1):
    if listo1 == []:
        return 0
    elif type(listo1[0]) != list:
        return listo1[0]+sum_all(listo1[1:])
    else:
        return sum_all(listo1[0])+sum_all(listo1[1:])
