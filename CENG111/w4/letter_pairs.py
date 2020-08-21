def letter_pairs(stringo):
    length_stri = len(stringo)
    if length_stri == 2:
        return [stringo]
    elif length_stri == 3:
        return [stringo[:2],stringo[1:]]
    else:
        return [stringo[:2]]+letter_pairs(stringo[1:])
