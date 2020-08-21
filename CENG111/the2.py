def isCovered(c_left,c_right,t1_left,t1_right,t2_left,t2_right):

    if t1_left[0] <= c_left[0] and t1_left[1] <= c_left[1] and t1_right[0] >= c_right[0] and t1_right[1] >= c_right[1]:
        return "COMPLETELY COVERED" #if tar1 consists of coal 
    elif t2_left[0] <= c_left[0] and t2_left[1] <= c_left[1] and t2_right[0] >= c_right[0] and t2_right[1] >= c_right[1]:
        return "COMPLETELY COVERED" #if tar2 consists of coal
    elif t1_left[0] <= c_left[0] and t1_left[1] <= c_left[1] and t1_right[0] <= c_right[0] and t1_right[1] >= c_right[1] and t2_left[0] <= t1_right[0] and t2_left[1] <= c_left[1] and t2_right[0] >= c_right[0] and t2_right[1] >= c_right[1]:
#        if t2_left[0] <= t1_right[0] and t2_left[1] <= c_left[1] and t2_right[0] >= c_right[0] and t2_right[1] >= c_right[1]:
        return "COMPLETELY COVERED" #if both tar1 and tar2 cover the coal
    elif t2_left[0] <= c_left[0] and t2_left[1] <= c_left[1] and t2_right[0] <= c_right[0] and t2_right[1] >= c_right[1] and t1_left[0] <= t2_right[0] and t1_left[1] <= c_left[1] and t1_right[0] >= c_right[0] and t1_right[1] >= c_right[1]:
#        if t1_left[0] <= t2_right[0] and t1_left[1] <= c_left[1] and t1_right[0] >= c_right[0] and t1_right[1] >= c_right[1]:
        return "COMPLETELY COVERED" #if both tar1 and tar2 cover the coal
    elif t1_left[0] <= c_left[0] and t1_left[1] <= c_left[1] and t1_right[0] >= c_right[0] and t1_right[1] <= c_right[1] and t2_left[0] <= c_left[0] and t2_left[1] <= t1_right[1] and t2_right[0] >= c_right[0] and t2_right[1] >= c_right[1]:
        return "COMPLETELY COVERED"
    elif t2_left[0] <= c_left[0] and t2_left[1] <= c_left[1] and t2_right[0] >= c_right[0] and t2_right[1] <= c_right[1] and t1_left[0] <= c_left[0] and t1_left[1] <= t2_right[1] and t1_right[0] >= c_right[0] and t1_right[1] >= c_right[1]:
        return "COMPLETELY COVERED"
    else:
        return "NOT COMPLETELY COVERED"
