def n_bit_Gray_code(n):
    list_to_return = []
    if n == 1:
        return ["0","1"]
    returned_list = n_bit_Gray_code(n-1)
    for elem in returned_list:
        elem_to_append = "0"+elem
        list_to_return.append(elem_to_append)
        elem_to_append = "1"+elem
        list_to_return.append(elem_to_append)
    return list_to_return

print (n_bit_Gray_code(3))