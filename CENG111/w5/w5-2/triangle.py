def triangle(n):
    list1 = []
    for i in range(n+1):
        add_space = (n-i)*" "
        add_star = (2*i-1) * "*"
        list1.append(add_space+add_star)
    return list1
