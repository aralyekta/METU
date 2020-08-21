def lis(list1):
    lengo = len(list1)
    listo = []
    len_longest = 0
    start_index = 0
    stop_index = 0
    for i in range(lengo-1):
        if list1[i] > list1[i+1] and i == 0:
            start_index = 1
            listo.append(1)
            continue
        elif list1[i] > list1[i+1]:
            print "Problem here"+str(i)
            stop_index = i
            leng = stop_index-start_index+1
            listo.append(leng)
            print "Appended"+str(leng)
            start_index = i+1
            continue
        elif list1[i] <= list1[i+1]:
            if i+2 == lengo:
                stop_index = i+1
                leng = stop_index-start_index+1
                listo.append(leng)
                print "Last one"+str(i)
            else:
                print "No Problem here"+str(i)
                continue
    return max(listo)

