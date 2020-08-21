def every(func,listo):
    if listo == []:
        return listo
    return [func(listo[0])]+every(func,listo[1:])
