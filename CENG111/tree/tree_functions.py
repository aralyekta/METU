def datum(tree):
    return tree[0]

def leftchild(tree):
    return tree[1]

def rightchild(tree):
    return tree[2]

def isleaf(tree):
    return tree[1] == [] and tree[2] == []

def isempty(tree):
    return tree == []

def makenode(datum, leftchild=[], rightchild = []):
    return [datum, leftchild, rightchild]


