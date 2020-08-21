def isPrime(num):
    if num == 1:
        return False
    for num_div in range(2,int(num **0.5)+1):
        if num % num_div == 0:
            return False
        else:
            continue
    return True

def check_equal(list1,list2):
    if len(list1) != len(list2):
        return False
    for elem in list1:
        if elem in list2:
            continue
        else:
            return False
    return True

def all_factorizations(num):
    list_to_return = []
    for num_div in range(2,int(num**0.5)+1):
        if num % num_div == 0:
            other_div = num // num_div
            if isPrime(other_div):
                return [[num_div,other_div]]
            else:
                listo = all_factorizations(other_div)
                listo.append([other_div])
            for elem in listo:
                state = True
                elem_to_append = [num_div]+elem
                for elem2 in list_to_return:
                    if check_equal(elem2,elem_to_append):
                        state = False
                        break
                    else:
                        continue
                if state == True:
                    list_to_return.append(elem_to_append)
        else:
            continue
    return list_to_return
print (all_factorizations(16))
print (all_factorizations(12))