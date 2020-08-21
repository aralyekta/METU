from tree_functions import *

def numparts(n):
    if n == 1:
        return [1]
    if n % 2 == 0:
        return [n,numparts(n/2),numparts(n/2)]
    elif n % 2 != 0:
        return [n,numparts(((n-1)/2)+1),numparts((n-1)/2)]
