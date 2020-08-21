def myrange(start,stop,incr):
    if start >= stop:
        return []
    return [start]+myrange(start+incr,stop,incr)
