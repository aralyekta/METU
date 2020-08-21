def counting_sort(list1,max1):
    array_count = []

    for i in range(max1+1):
        howmany = list1.count(i)
        array_count.append(howmany)

    array_to_return = []

    for number in range(len(array_count)):
        while array_count[number] > 0:
            array_to_return.append(number)
            array_count[number] -= 1

    return array_to_return
