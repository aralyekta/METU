def return_first_int(list1):
    num = []
    count = 0
    leng = len(list1)
    i = 0
    for a in range(leng):
        elem = list1[i]
        if type(elem) in (int,long,float):
            if count == 0:
                num.append(elem)
                count += 1
                list1.remove(elem)
            elif count == 1:
                list1.remove(elem)
        else:
            i +=1
            continue
    if num == []:
        return num
    else:
        return int(num[0])

def first_in_its_level(list1):
    queue = list1
    list_to_return = []
    while(queue):
        number = return_first_int(queue)
        if number != []:
            list_to_return.append(number)
        leng = len(queue)
        for i in range(leng):
            elem = queue[0]
            for in_elem in elem:
                queue.append(in_elem)
            queue.remove(elem)
    
    return list_to_return
