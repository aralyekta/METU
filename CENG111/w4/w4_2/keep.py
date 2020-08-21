def keep(func,listo):
    if listo == []:
        return listo
    if func(listo[0]):
        return [listo[0]]+keep(func,listo[1:])
    else:
        return keep(func,listo[1:])
