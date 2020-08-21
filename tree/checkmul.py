def checkmul(tree):
    if tree[1] == [] and tree[2] == []:
        return True
    return tree[1][0] * tree[2][0] == tree[0] and checkmul(tree[1]) and checkmul(tree[2])

