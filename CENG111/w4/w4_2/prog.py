def progressive_square(listo):
    if len(listo) <=1
        return True
    if listo[1] == listo[0]**2:
        return True and progressive_square(listo[1:])
    else:
        return False
