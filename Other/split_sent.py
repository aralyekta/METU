x = raw_input()
first_point = x.find(" ")
#y = x[first_point+1:]
second_point = x[first_point+1:].find(" ") + first_point + 1
print x[:first_point] 
print x[first_point+1:second_point]
print x[second_point + 1:]
