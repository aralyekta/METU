def progressive_square(listo):
    if listo == []:
        return True
    if listo[1] == listo[0] ^ 2 and progressive_square(listo[1:]):
        return True
    else:
        return False

