a = float(raw_input())
b = float(raw_input())
c = float(raw_input())

delta = b ** 2 - 4 * a * c
x1 = (-b + delta ** 0.5)/(2 * a)
x2 = (-b - delta ** 0.5)/(2 * a)
print delta
print x1
print x2
