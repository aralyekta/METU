def remove_duplicate(str1):
    if len(str1) == 1:
        return str1
    recursed_str = remove_duplicate(str1[1:])
    if str1[0] == recursed_str[0]:
        return recursed_str
    else:
        return str1[0]+recursed_str

print (remove_duplicate('geeksforgeeeeek'))
print (remove_duplicate('acaaabbbacdddd'))
