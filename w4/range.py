def myrange(num1,num2,num3):
    if num1 >= num2:
        return []
    elif num1+num3 > num2:
        return [num1]
    else:
        return [num1]+myrange(num1+num3,num2,num3)
