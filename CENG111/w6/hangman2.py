def remove_till_end(str1,char):
	list1 = list(str1)
	while char in list1:
		list1.remove(char)
	str1 = "".join(list1)
	return str1

def hangman(str1,str2,num):
	errors = 0
	len2 = len(str2)
	for i in range(len2):
		if str2[i] not in str1:
			errors += 1
			if errors > num:
				return "lose"
			print str2[i]+"Isn't in, moving on."
			continue
		elif str2[i] in str1:
			str1 = remove_till_end(str1,str2[i])
			print "removed"+str2[i]
		if str1 == "":
			return "win"
	print str1

	if str1 != "":
		return "lose"

hangman('sixbynineis42', 'sixbynineis42', 0)
