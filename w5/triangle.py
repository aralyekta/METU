def triangle(n):
    list1 = []
    for i in range(n+1):
        if i == 0:
            continue
        to_be_added_empty = " "*int(n-i)
        print "Starting" + to_be_added_empty + "Stopping"
        to_be_added_star = (2*i-1)*"*"
        list1.append(to_be_added_empty+to_be_added_star)
    return list1
