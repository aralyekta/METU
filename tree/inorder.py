def inorder(tree):
    if tree[1] == [] and tree[2] == []:
        return [tree[0]]
    list_to_return = []
    list_to_return.extend(inorder(tree[1]))
    list_to_return.append(tree[0])
    list_to_return.extend(inorder(tree[2]))
    return list_to_return
