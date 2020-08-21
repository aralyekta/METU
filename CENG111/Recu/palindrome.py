def is_palindrome(str1):
    if str1 == "":
        return True
    return str1[0] == str1[-1] and is_palindrome(str1[1:-1])
    