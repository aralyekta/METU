def isprime(n):
    for i in range(2,(n**0.5)):
        if n % i == 0:
            return False
    return True
