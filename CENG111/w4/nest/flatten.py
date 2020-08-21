def flatten(list1):
    if list1 == []:
        return []
    elif type(list1[0]) != list:
        return [list1[0]]+flatten(list1[1:])
    else:
        return flatten(list1[0])+flatten(list1[1:])
