def normalize_index(index, length):
    if index >= 0:
        return index if index < length else length-1
    else:
        return length + index if -index < length else 0

def slice_rec(lst, start, end, step):
    if (step > 0 and start >= end) or (step < 0 and start <= end):
        return []
    return [lst[start]] + slice_rec(lst, start+step, end, step)

def slice(lst, start, end, step):
    s = normalize_index(start, len(lst))
    e = normalize_index(end, len(lst))
    result = slice_rec(lst, s, e, step)
    if step > 0 and end > len(lst):
        result.append(lst[-1])
    if step < 0 and -end > len(lst):
        result.append(lst[0])
    return result
