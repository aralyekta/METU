def roots(a,b,c):
    delta = b ** 2 - 4*a*c
    root1 = (-b + delta ** 0.5)/(2*a)
    root2 = (-b - delta ** 0.5)/(2*a)
    return (root1,root2)

print roots(2,9,4)
