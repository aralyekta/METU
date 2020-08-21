def check_parantheses(str1):
    open_brackets = ("(","[","{")
    close_brackets = (")","]","}")
    stack = []
    leng = len(str1)
    for i in range(leng):
        if str1[i] in open_brackets:
            stack.append(str1[i])
        elif str1[i] in close_brackets:
            if len(stack) == 0:
                return False
            elif open_brackets.index(stack[-1]) == close_brackets.index(str1[i]):
                stack.pop()
    if stack == []:
        return True
    else:
        return False
