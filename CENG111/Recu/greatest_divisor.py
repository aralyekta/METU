def gcd(num1,num2):
    big_num = max(num1,num2)
    small_num = min(num1,num2)
    kalan = big_num % small_num
    if kalan == 0:
        return small_num
    else:
        return gcd(small_num,kalan)

print (gcd(32,16))
print (gcd(72,192))
print (gcd(16,15))