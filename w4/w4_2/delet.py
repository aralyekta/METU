def remove_item(str1,listo):
    if listo == []:
        return listo
    if str1 == listo[0]:
        return remove_item(str1,listo[1:])
    return [listo[0]]+remove_item(str1,listo[1:])
