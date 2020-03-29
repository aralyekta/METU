from tree_functions import *

def isordered(tree):
    if ischild(tree):
        return True
    return isordered(tree[1]) and isordered(tree[2]) and tree[1][0] < tree[0] < tree[2][0]
