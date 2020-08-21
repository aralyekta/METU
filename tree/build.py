def isleaf(tree):
    return len(tree) == 1

def build(tree):
    if isleaf(tree):
        return tree[0]
    if tree[0] == "string":
        return str(build(tree[1]))+str(build(tree[2]))
    elif tree[0] == "list":
        return [build(tree[1])]+[build(tree[2])]
