def keep_numbers(listo):
    if listo == []:
        return listo
    if type(listo[0]) in (int,long,float):
        return [listo[0]]+keep_numbers(listo[1:])
    else:
        return keep_numbers(listo[1:])

