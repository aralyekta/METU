def remove_item(num1,listo):
    if listo == []:
        return listo
    if num1 == listo[0]:
        return remove_item(num1,listo[1:])
    else:
        return [listo[0]]+remove_item(num1,listo[1:])
        
