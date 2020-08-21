from tree_functions import *
def increasing_path(tree):
    first_case = False
    second_case = False
    if isleaf(tree) or isempty(tree):
        return True
    elif not isleaf(tree) and not isempty(tree):
        if tree[1] != [] and tree[0] < tree[1][0]:
            first_case = increasing_path(tree[1])
            print first_case
        if tree[2] != [] and tree[0] < tree[2][0]:
            second_case = increasing_path(tree[2])
            print second_case
    	return first_case or second_case
