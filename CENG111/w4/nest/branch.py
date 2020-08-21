def branch(list1,list2):
    if len(list1) == 1:
        return list2[list1[0]]
    return branch(list1[1:],list2[list1[0]])

