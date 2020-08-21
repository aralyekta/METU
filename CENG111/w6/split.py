def find_first(str1,list1):
    leng = len(list1)
    if leng == 1:
        return str1.find(list1[0])
    else:
        a = str1.find(list1[0])
        for i in range(1,leng):
            point = str1.find(list1[i])
            if (point < a or a == -1) and point != -1:
                a = point
        return a

def split(str1,list1):
    list_to_return = []
    if str1 == "":
        list_to_return.append(str1)
    while str1 != "":
        a = find_first(str1,list1)
        if a == -1:
            list_to_return.append(str1)
            break
        else:
            list_to_return.append(str1[:a])
        str1 = str1[a+1:]
    return list_to_return
