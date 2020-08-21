def arithmetic(listo):
    inst = listo[0]
    num1 = listo[1] 
    num2 = listo[2] 
    if inst == 'add':
        return num1 + num2
    elif inst == 'minus':
        return num1-num2
    elif inst == 'mult':
        return num1*num2
    elif inst == 'div':
        return num1/num2
    elif inst == 'max':
        return max(num1,num2)
    elif inst == 'min':
        return min(num1,num2)
print arithmetic(['add', 3, 5])
print arithmetic(['minus', 5, 7])
print arithmetic(['mult', 5.0, 7/3])
print arithmetic(['div', 7, 3])
print arithmetic(['max', 7, 3])
print arithmetic(['min', 7, 3])
