def maxdepth(tree):
    if tree == []:
        return 0
    return max(maxdepth(tree[1]),maxdepth(tree[2])) +1
