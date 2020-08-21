firstnum = raw_input()
secondnum = raw_input()

num1_A = firstnum.count('A')
num1_B = firstnum.count('B')
num2_A = secondnum.count('A')
num2_B = secondnum.count('B')

num1 = str(num1_A) + str(num1_B)
num2 = str(num2_A) + str(num2_B)

print int(num1)*int(num2)
