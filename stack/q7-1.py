def mutable_elements(tuple1):
    stack = []
    mutable_list = []
    for elem in tuple1:
        stack.append(elem)

    while(stack):
        if type(stack[-1]) == list:
            list1 = stack.pop()
            mutable_list.append(list1)
        elif type(stack[-1]) == tuple:
                tuple2 = stack.pop()
                for elem2 in tuple2:
                    stack.append(elem2)
        else:
            stack.pop()

    return mutable_list
