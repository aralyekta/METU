def count_item(stringo,listo):
    if listo == []:
        return 0
    return int(stringo == listo[0]) + count_item(stringo,listo[1:])


