def sum_numbers(listo):
    if listo == []:
        return 0
    if type(listo[0]) in (float,int,long):
        return listo[0]+sum_numbers(listo[1:])
    else:
        return sum_numbers(listo[1:])
