def is_substring(str1,str2):
    when = str2.find(str1)
    if str1 == "":
        return True
    return str1[0] == str2[when] and is_substring(str1[1:],str2[when+1:])
