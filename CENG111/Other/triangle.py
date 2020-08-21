a = float(raw_input())
b = float(raw_input())
c = float(raw_input())
circumference = a+b+c
u = circumference/2
area = (u * (u-a) * (u-b) * (u-c)) ** (1.0/2)
print circumference
print area
