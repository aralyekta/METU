def letter_pairs(str1):
    if len(str1) <= 1:
        return []
    [str1[:2]]+letter_pairs(str1[1:])
