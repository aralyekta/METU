def check_if_palin(n):
    binary = bin(n)[2:]
    if str(n)[::-1] == str(n) and str(binary)[::-1] == str(binary):
        return True
    else:
        return False

def palindromes(n):
    list_return = []
    for i in range(n+1):
        if check_if_palin(i):
            list_return.append(i)
    return list_return
