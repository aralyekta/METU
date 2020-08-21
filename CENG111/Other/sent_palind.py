def ispalindrome(listo):
    stringo = ''.join(listo)
    return stringo == stringo[::-1]
'''    if len(stringo) % 2 == 1:
        i = 1
    else:
        i = 0
    stringo_1 = stringo[:len(stringo)/2+i]
    print stringo_1
    stringo_2 = stringo[-1:len(stringo)/2-1:-1]
    print stringo_2
    if stringo_2 == stringo_1:
        return True
    else:
        return False'''

print ispalindrome(['mr', 'owl', 'ate', 'my', 'metal', 'worm'])
print ispalindrome(['ceng', '111'])
print ispalindrome(['abcd', 'dcba'])
print ispalindrome(['abcd', 'cba'])
