def remove_till_end(str1,char):
	list1 = list(str1)
	while char in list1:
		list1.remove(char)
	str1 = "".join(list1)
	return str1

def hangman(str1,str2,num):
	errors = 0
	len2 = len(str2)
	i = 0
	while i < range(len2):
		if str2[i] not in str1:
			errors += 1
			i += 1
			if errors > num:
				return "lose"
			print str2[i]+"Isn't in, moving on."
			continue
		elif str2[i] in str1:
			str1 = remove_till_end(str1,str2[i])
			str2 = remove_till_end(str2,str2[i])
			print "removed from both lists"+str2[i]
			print str1+":"+str2
		if str1 == "":
			return "win"
		len2 = len(str2)
	print str1

	if str1 != "":
		return "lose"

hangman('sixbynineis42', 'sixbynineis42', 0)
