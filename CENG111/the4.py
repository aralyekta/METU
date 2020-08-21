def which_word(string):
	if string[::-1][:4] == "lliw":
		return string[:-4],"will"
	elif string[::-1][:4] == "nepo":
		return string[:-4],"open"
	elif string[::-1][:6] == "desolc":
		return string[:-6],"closed"

def isleaf(tree):
	if len(tree) == 2 and type(tree[1]) == int :
		return True
	else:
		return False

def convert_tree_first(tree):
	leng = len(tree[0])
	list_to_return = [tree[0]+"open"]
	if isleaf(tree):
		return [tree[0]+"open"]+[tree[1]]
	children_amount = len(tree)-1
	for child in range(1,children_amount+1):
		returned_list = convert_tree_first(tree[child])
		list_to_return.append(returned_list)
	return list_to_return

def convert_tree(tree):
	tree_to_return = [tree[0]]
	if isleaf(tree):
		returned_tuple_for_word = which_word(tree[0])
		if tree[1] == 1 and returned_tuple_for_word[1] == "open":
			word_to_return = returned_tuple_for_word[0]+"will"
			return [word_to_return,tree[1]]
		else:
			return tree
	children_amount = len(tree)-1
	for child in range(1,children_amount+1):
		returned_tuple = convert_tree(tree[child])
		tree_to_return.append(returned_tuple)
	return tree_to_return 

def findmax(tree):
	list_to_choose = []
	if isleaf(tree):
		return tree[1]
	children_amount = len(tree) -1
	for child in range(1,children_amount+1):
		list_to_choose.append(findmax(tree[child]))
	return max(list_to_choose)

def oneturn(tree):
	list_to_return = [tree[0]]
	if isleaf(tree):
		return [tree[0]]+[tree[1]-1]
	children_amount = len(tree) -1
	for child in range(1,children_amount+1):
		list_to_return.append(oneturn(tree[child]))
	return list_to_return

def carry_will(tree):
	#print "tree before:" + str(tree)
	list_to_compare = []
	if isleaf(tree):
		return tree[0]
	state = True
	child_amount = len(tree)-1
	#print "child amount is:" + str(child_amount)
	for child in range(1,child_amount+1):
		elem_to_be_cropped = carry_will(tree[child])
		#print str(type(elem_to_be_cropped)) + " elem to be cropped:" + str(elem_to_be_cropped)
		if type(elem_to_be_cropped) == tuple:
			elem_to_be_appended = which_word(elem_to_be_cropped[0])[1]
		else:
			elem_to_be_appended = which_word(elem_to_be_cropped)[1]

		#print "elem to be appended:" + str(elem_to_be_appended)
		list_to_compare.append(elem_to_be_appended)
		#print "list to compare:" + str(list_to_compare)
	elem_to_compare = list_to_compare[0]
	for elem in list_to_compare:
		if elem == elem_to_compare:
			continue
		elif elem != elem_to_compare:
			state = False
			break
	if state == True:
		subpart = which_word(tree[0])[0]
		tree[0] = subpart + elem_to_compare
	#print "tree after:" + str(tree)
	return tree[0],tree

def check_changes(tree_before,tree_after):
	list_of_closed = []
	if not isleaf(tree_after) and tree_after[0] != tree_before[0]:
		#print "case1:"
		tap_name = which_word(tree_after[0])[0]
		list_of_closed.append(tap_name)
		#print "List of closed:" + str(list_of_closed)
		return list_of_closed
	elif isleaf(tree_after):
		if tree_after[0] != tree_before[0]:
			#print "case2:"
			tap_name = which_word(tree_after[0])[0]
			list_of_closed.append(tap_name)
			#print "List of closed:" + str(list_of_closed)
			return list_of_closed
		elif tree_after[0] == tree_before[0]:
			#print "case3:"
			#print "List of closed:" + str(list_of_closed)
			return list_of_closed
	else:
		#print "case4:"
		child_amount = len(tree_after)-1
		for child in range(1,child_amount+1):
			#print "Child is:" + str(tree_after)
			list_to_extend = check_changes(tree_before[child],tree_after[child])
			#print "List to extend is:" + str(list_to_extend)
			list_of_closed.extend(list_to_extend)
		#print "List of closed:" + str(list_of_closed)
		return list_of_closed

def chalchiuhtlicue(tree):
	list_to_return = []
	if isleaf(tree):
		turn_amount = tree[1]
		for turn in range(turn_amount-1):
			list_to_return.append([])
		list_to_return.append([tree[0]])
		return list_to_return
	turn_amount = findmax(tree)
	converted_first_tree = convert_tree_first(tree)
	converted_with_will = convert_tree(converted_first_tree)
	#print converted_with_will
	with_carried_will = carry_will(converted_with_will)
	#print with_carried_will
	tree_with_carried_will = with_carried_will[1]
	list_of_changed = check_changes(converted_first_tree,tree_with_carried_will)
	list_to_return.append(list_of_changed)
	#print list_of_changed
	oneturned_tree = oneturn(tree_with_carried_will)
	#print oneturned_tree
	for turn in range(turn_amount-1):
		converted_with_will = convert_tree(oneturned_tree)
		#print converted_with_will
		with_carried_will = carry_will(converted_with_will)
		#print with_carried_will
		tree_with_carried_will = with_carried_will[1]
		#print tree_with_carried_will
		list_of_changed2 = check_changes(oneturned_tree,tree_with_carried_will)
		#print list_of_changed2
		list_to_return.append(list_of_changed2)
		oneturned_tree = oneturn(tree_with_carried_will)
		#print oneturned_tree
	return list_to_return