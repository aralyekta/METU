def add(str2,listo):
    if listo == []:
        return listo
    return [str2+listo[0]]+add(str2,listo[1:])

def substrings(str1):
    if len(str1) == 1:
        return [str1]
    return [str1[0]]+add(str1[0],substrings(str1[1:]))+substrings(str1[1:])

