def sum_tree(tree):
    if tree[1] == [] and tree[2] == []:
        return tree[0]
    elif tree[1] == []:
        return tree[0] + sum_tree(tree[2])
    elif tree[2] == []:
        return tree[0] + sum_tree(tree[1])
    else:
        return tree[0] + sum_tree(tree[1]) + sum_tree(tree[2])
