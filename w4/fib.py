def fibseries(num):
    if num == 1:
        return [0]
    elif num == 2:
        return [0,1]
    series = fibseries(num-1)
    new_num = series[-1] + series[-2]
    series.append(new_num)
    return series

