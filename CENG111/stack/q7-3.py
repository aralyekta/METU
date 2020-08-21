def expand_BOM(str1):
    if str1.find(".") == -1:
        return str1
    queue = []
    for elem in str1:
        queue.append(elem)
    queue_to_return = []
    while(queue):
        if queue[0] != ".":
            if queue_to_return == []:
                queue_to_return.append(queue[0])
            else:
                leng3 = len(queue_to_return)
                for asd in range(leng3):
                    elem = queue_to_return[0]
                    append1 = elem+queue[0]
                    queue_to_return.append(append1)
                    queue_to_return.remove(elem)
            queue.remove(queue[0])
        elif queue[0] == ".":
            if str1.find(".") == 0:
                append1 = "b"
                append2 = "m"
                append3 = "o"
                queue_to_return.append(append1)
                queue_to_return.append(append2)
                queue_to_return.append(append3)
            else:
                leng2 = len(queue_to_return)
                for i in range(leng2):
                    elem = queue_to_return[0]
                    append1 = elem+"b"
                    append2 = elem+"m"
                    append3 = elem+"o"
                    queue_to_return.remove(elem)
                    queue_to_return.append(append1)
                    queue_to_return.append(append2)
                    queue_to_return.append(append3)
            queue.remove(queue[0])
    return queue_to_return


