def flatten(list1):
    list_to_return = []
    for elem in list1:
        if type(elem) != list:
            list_to_return.extend([elem])
        elif type(elem) == list:
            list_to_extend = flatten(elem)
            list_to_return.extend(list_to_extend)
    return list_to_return

print (flatten(['ahmet AKHUNLAR',[1930,1998],[['ayse'],'mehmet',['aliye',['yakup','veli']]],[],1.85]))