num = raw_input()

num1= num[::2]
num2= num[1::2]

x= (int(num1) + int(num2)) % int(num[-1])
new_char = chr(ord("A")+x)

print new_char+str(int(num1)+int(num2))
