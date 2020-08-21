def hangman(str1,str2,num):
    len1 = len(str1)
    len2 = len(str2)
    if len1 > len2:
        return "lose"
    elif str1 == str2:
        return "win"
    elif len1 == len2 and str1 != str2:
        return "lose"
    a = 0
    for i in range(len2):
        if str1[i] == str2[i]:
            continue
        else:
            a+= 1

        if a >= num:
            return "lose"

    return "win"
