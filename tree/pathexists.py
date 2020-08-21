def path_exists(tree,string):
    if string == "":
        return True
    if tree[1] == [] and tree[2] == []:
        if len(string) == 1 and string[0] == tree[0]:
            return True
        else:
            return False
    if tree[0] == string[0]:
        return path_exists(tree[1],string[1:]) or path_exists(tree[2],string[1:])
    elif tree[0] != string[0]:
        return path_exists(tree[1],string) or path_exists(tree[2],string)

