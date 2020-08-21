def k_possible(str1,num):
    list_to_return = []
    if num == 0:
        return [""]
    list_smaller = k_possible(str1,num-1)
    for char in str1:
        for elem in list_smaller:
            new_elem = char + elem
            list_to_return.append(new_elem)
    return list_to_return