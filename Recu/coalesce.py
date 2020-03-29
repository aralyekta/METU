def coalesce(list_of_list):
    print (list_of_list)
    if len(list_of_list[0]) == 2 and type(list_of_list[0][0]) != list:
        return list_of_list[0]
    returned_list = coalesce(list_of_list[0:])
    print (returned_list)
    leng = len(list_of_list[0])
    print 
    for num in range(leng):
        print (num)
        elem_curr = list_of_list[0][num]
        print (elem_curr)
        if num == 0:
            elem_other = list_of_list[0][1]
        elif num == 1:
            elem_other = list_of_list[0][0]

    return returned_list

print (coalesce([['g','m'],['p','t']])) 