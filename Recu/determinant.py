def determinant(list1):
    result = 0
    leng = len(list1)
    if leng == 2:
        return list1[0][0]*list1[1][1]-list1[0][1]*list1[1][0]
    #row_final_list = []
    for elem_num in range(leng):
        row_list = []
        for row_num in range(1,leng):
            row_to_add = list1[row_num][:elem_num]+list1[row_num][elem_num+1:]
            row_list.append(row_to_add)
        #row_final_list.append(row_list)
        if elem_num % 2 == 0:
            result += list1[0][elem_num] * determinant(row_list)
        elif elem_num % 2 == 1:
            result -= list1[0][elem_num] * determinant(row_list)
        print (row_list)
    return result
    #print (row_final_list)

#determinant([["a","b","c","d"],["e","f","g","h"],["x","y","z","u"],["i","j","k","l"]])
print (determinant([[0.4,0,1.2,-4],[7.5,1.1,-0.9,3.9],[11.25,6.8,7.1,12.1],[0,5.7,-0.12,-17.2]]))