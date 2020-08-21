def find_line(list_before):
    leng = len(list_before)
    if leng == 1:
        return [1,1]
    row_to_add_to_middle = []
    for i in range(leng-1):
        a = list_before[i]+list_before[i+1]
        row_to_add_to_middle.append(a)
    return [1]+row_to_add_to_middle+[1]
    

def pascal(n):
    list_to_return = [[1]]
    for i in range(n-1):
        if i == 0:
            listo = [1]
        listo = find_line(listo)
        list_to_return.append(listo)
    return list_to_return


