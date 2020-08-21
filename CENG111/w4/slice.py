def slice(listo,start,stop,increment):
    length_list = len(listo)
    if increment > 0:
        if start >= stop or start >=length_list:
            return []
        else:
            start = start % length_list
            if stop < 0:
                stop = stop % length_list
            return [listo[start]]+slice(listo,start+increment,stop,increment)
    elif increment < 0:
        if stop == 0:
            stop = -length_list
        if start <= stop or abs(start) > abs(length_list):
            return []
        else:
            return [listo[start]]+slice(listo,start+increment,stop,increment)

