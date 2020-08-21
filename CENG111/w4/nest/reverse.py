def reverse_list(list1):
    if len(list1) == 1 and type(list1[0]) != list:
        return [list1[0]]
    if list1 == []:
        return []
    elif type(list1[-1]) != list:
        return [list1[-1]]+reverse_list(list1[:-1])
    elif type(list1[-1]) == list:
        return [reverse_list(list1[-1])]+reverse_list(list1[:-1])

