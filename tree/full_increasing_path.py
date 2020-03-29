from tree_functions import *

def increasing_path(tree):
    if isleaf(tree) or isempty(tree):
        return True
    if tree[1][0] > tree[0] and tree[2][0] > tree[0]:
        return increasing_path(tree[1]) and increasing_path(tree[2])
    else:
        return False
