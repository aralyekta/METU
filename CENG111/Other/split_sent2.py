delimiter = raw_input()
len_delimiter = len(delimiter)
x = raw_input()
first_point = x.find(delimiter)
second_point = x[first_point+len_delimiter:].find(delimiter) + first_point + len_delimiter
print x[:first_point] 
print x[first_point+len_delimiter:second_point]
print x[second_point + len_delimiter:]
