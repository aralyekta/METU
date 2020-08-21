link = raw_input()
what_to = raw_input()
link += "&"
what_to += "="

start = link.find(what_to)
stop = link.find("&", start+ len(what_to))
length = stop - start - len(what_to)
desired_string = link[start+len(what_to):stop]
print desired_string
