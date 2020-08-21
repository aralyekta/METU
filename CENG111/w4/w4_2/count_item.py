def count_item(str1, listo):
    if listo == []:
        return 0
    if listo[0] == str1:
        return 1 + count_item(str1,listo[1:])
    else:
        return count_item(str1,listo[1:])
