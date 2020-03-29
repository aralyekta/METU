string = raw_input()

first_point = string.find("<reverse>")
second_point = string.find("</reverse>")
decoded = string[second_point-1:first_point+8:-1]

new_string = string[:first_point] + decoded + string[second_point+len("</reverse>"):]
print new_string
