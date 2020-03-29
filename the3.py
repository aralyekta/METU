import sys

mapname = sys.argv[1]
instname = sys.argv[2]
stop = sys.argv[3]

def pull_map(filename):
    f = open(filename,"r")
    map_to_return = f.read()
    f.close()
    return map_to_return

def pull_instr(filename):
    f = open(filename,"r")
    rules = f.read()
    f.close()
#    #print rules
    list_to_return= rules.split()
    return list_to_return

def str_to_list(list1): #Helper
    list_to_return = []
    list1 = str(list1)[2:-2]
    for i in range(len(list1)):
        list_to_return.append(list1[i])
    return list_to_return

def map_to_array_first(filename):
    map_list = []
    f = open(filename, "r")

    for line in f:
        elems = line.split()
        map_list.append(elems)
#        #print map_list
    return map_list

def map_to_array(str1):
    map_list = []
    if str1.find("\n") == -1:
        return [[str1]]
    else:
        stop = str1.find("\n")
        while str1.find("\n") != -1:
            map_list.append([str1[:stop]])
            str1 = str1[stop+1:]
        map_list.append([str1])
    return map_list

def list_to_smaller(list1):
    list_to_return = []
    for i in range(len(list1)):
        list_to_append = str_to_list(list1[i])
        list_to_return.append(list_to_append)
    return list_to_return

def check_boxes(list1):
	contact_info = []
	rows = len(list1)
	columns = len(list1[0])
	if rows == 1 and columns == 1:
		return [[0]]
	elif rows == 1:
		contact_to_append = []
		for column in range(columns):
			contact = 0
			if column == 0:
				if list1[0][column+1] == "*":
					contact += 1
			elif column == columns-1:
				if list1[0][column-1] == "*":
					contact += 1
			else:
				if list1[0][column-1] == "*":
					contact += 1
				if list1[0][column+1] == "*":
					contact += 1
			contact_to_append.append(contact)
		contact_info.append(contact_to_append) 
	elif columns == 1:
		contact_to_append = []
		for row in range(rows):
			contact = 0
			if row == 0:
				if list1[row+1][0] == "*":
					contact += 1
			elif row == rows-1:
				if list1[row-1][0] == "*":
					contact += 1
			else:
				if list1[row-1][0] == "*":
					contact += 1
				if list1[row+1][0] == "*":
					contact += 1
			contact_to_append.append([contact])
		contact_info = contact_to_append
	else:
		for row in range(rows):
			contact_to_append = []
			for column in range(columns):
				contact = 0
				if row == 0 and column == 0:
					if list1[0][1] == "*":
						contact += 1
					if list1[1][0] == "*":
						contact += 1
					if list1[1][1] == "*":
						contact += 1
				elif row == rows-1 and column == columns-1:
					if list1[row][column-1] == "*":
						contact += 1
					if list1[row-1][column] == "*":
						contact += 1
					if list1[row-1][column-1] == "*":
						contact += 1
				elif row == 0 and column == columns-1:
					if list1[row][column-1] == "*":
						contact += 1
					if list1[row+1][column] == "*":
						contact += 1
					if list1[row+1][column-1] == "*":
						contact += 1
				elif row == rows-1 and column == 0:
					if list1[row-1][column] == "*":
						contact += 1
					if list1[row][column+1] == "*":
						contact += 1
					if list1[row-1][column+1] == "*":
						contact += 1
				elif row == 0:
					if list1[row][column-1] == "*":
						contact += 1
					if list1[row][column+1] == "*":
						contact += 1
					if list1[row+1][column-1] == "*":
						contact += 1
					if list1[row+1][column] == "*":
						contact += 1
					if list1[row+1][column+1] == "*":
						contact += 1
				elif column == 0:
					if list1[row-1][column] == "*":
						contact += 1
					if list1[row+1][column] == "*":
						contact += 1
					if list1[row][column+1] == "*":
						contact += 1
					if list1[row-1][column+1] == "*":
						contact += 1
					if list1[row+1][column+1] == "*":
						contact += 1
				elif row == rows-1:
					if list1[row][column-1] == "*":
						contact += 1
					if list1[row][column+1] == "*":
						contact += 1
					if list1[row-1][column-1] == "*":
						contact += 1
					if list1[row-1][column] == "*":
						contact += 1
					if list1[row-1][column+1] == "*":
						contact += 1
				elif column == columns-1:
					if list1[row-1][column] == "*":
						contact += 1
					if list1[row+1][column] == "*":
						contact += 1
					if list1[row-1][column-1] == "*":
						contact += 1
					if list1[row][column-1] == "*":
						contact += 1
					if list1[row+1][column-1] == "*":
						contact += 1
				else:
					if list1[row][column-1] == "*":
						contact += 1
					if list1[row][column+1] == "*":
						contact += 1
					if list1[row-1][column] == "*":
						contact += 1
					if list1[row+1][column] == "*":
						contact += 1
					if list1[row-1][column-1] == "*":
						contact += 1
					if list1[row-1][column+1] == "*":
						contact += 1
					if list1[row+1][column-1] == "*":
						contact += 1
					if list1[row+1][column+1] == "*":
						contact += 1
				contact_to_append.append(contact)
			contact_info.append(contact_to_append)
	return contact_info

def check_rules(rules_list,contact_list,old_list):
    new_map = []
    rows = len(contact_list)
    columns = len(contact_list[0])
    inst_amount = len(rules_list)
    for row in range(rows):
        row_to_append = []
        for column in range(columns):
            leng = len(row_to_append)
            for instr in range(inst_amount):
                instr_current = rules_list[instr]
                curr_char = str(instr_current[0])
                operator = str(instr_current[1])
                amount = str(instr_current[2])
                char_to = str(instr_current[3])
                ##print str(row)+"th row" + str(column)+"th column " + "Symbol is: " + map_list[row][column] + " Contact info is:" +str(contact_info[row][column])+" Now evaluating: " +str(instr)+curr_char+operator+str(amount)+char_to
                if operator == "=" and old_list[row][column] == curr_char and contact_list[row][column] == int(amount):
                    row_to_append.append(char_to)
#                    #print "Check if equal. Appended"+char_to
                elif operator == "<" and old_list[row][column] == curr_char and contact_list[row][column] < int(amount):
                    row_to_append.append(char_to)
#                    #print "Check if less. Appended"+char_to
                elif operator == ">" and old_list[row][column] == curr_char and contact_list[row][column] > int(amount):
                    row_to_append.append(char_to)
#                    #print "Check if more. Appended"+char_to
            if len(row_to_append) == leng:
                row_to_append.append(old_list[row][column])
#                #print "No change, appended " + str(old_list[row][column])
        new_map.append(row_to_append)
#        #print row_to_append
#    #print new_map
    return new_map

def list_to_map(list1):
    string_to_return = ""
    for i in range(len(list1)):
        row_to_add = ""
        for a in range(len(list1[i])):
            row_to_add += str(list1[i][a])
        leng = len(list1)
        if i != leng-1:
            row_to_add += "\n"

        string_to_return += row_to_add
#    string_to_return.()
#    #print string_to_return
    return string_to_return

def func(mapname,instname,stop):
    if int(stop) == 0:
        map_to_continue = pull_map(mapname)
    else:
        map_to_continue = ""
        start = 0
        inst_list = pull_instr(instname)
        ##print inst_list
        for i in range(int(stop)):
            ##print start < stop
            ##print str(start) +"AND"+str(stop)
            if start == 0:
                map_list = map_to_array_first(mapname)
                #print "1st1" + str(map_list)
                map_list_new = list_to_smaller(map_list)
                #print "2nd1" + str(map_list_new)
                contact_info = check_boxes(map_list_new)
                #print "3rd1"+ str(contact_info)
                new_map = check_rules(inst_list,contact_info,map_list_new)
                #print "4th1"+str(new_map)
                string_to_continue = list_to_map(new_map)
                #print "5th1"+str(string_to_continue)
                map_to_continue = string_to_continue
                start += 1
                #print "6th1"+str(map_to_continue)
            else:
                map_list = map_to_array(map_to_continue)
                #print "1st2" + str(map_list)
                map_list_new = list_to_smaller(map_list)
                #print "2nd2"+str(map_list_new)
                contact_info = check_boxes(map_list_new)
                #print "3rd2"+str(contact_info)
                new_map = check_rules(inst_list,contact_info,map_list_new)
                #print new_map
                string_to_continue = list_to_map(new_map)
                #print "4rd2"+ str(string_to_continue)
                map_to_continue = string_to_continue
                #print "5rd2" + str(map_to_continue)
                #print "6th2"
                start += 1
    if map_to_continue[-1] == "\n":
        print map_to_continue[:-1]
    else:
    	print map_to_continue

func(mapname,instname,stop)
