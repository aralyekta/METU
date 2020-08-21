def divide_and_destroy(list1):
    count = 0
    while list1 != []:
        stack = []
        for elem in list1:
            num = elem/2
            if num != 0:
                stack.append(num)
            list1 = stack
            print stack
        count += 1
    return count
