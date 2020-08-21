def flatten(list1):
    stack = []
    for elem in list1:
        if type(elem) != list:
            stack.append(elem)
        elif type(elem) == list:
            for elem2 in elem:
                stack.append(elem2)

    return stack
