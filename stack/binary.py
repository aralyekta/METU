def binary(list1,start,stop,key):
    middle = (start+stop)/2
    while key != list1[middle]:
        middle = (start+stop)/2
        if start > stop:
            return -1    
        elif key < list1[middle]:
            stop = middle-1
            continue
        elif key > list1[middle]:
            start = middle+1
            continue
    else:
        return middle
