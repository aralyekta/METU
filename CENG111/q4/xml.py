def complete_XML_tags(stri):
    tag1 = stri[:stri.find(">")+1]
    tag2 = stri[stri.find(">")+1:]
    if (tag2 == tag1[:1] + "/" + tag1[1:]):
        return (True,stri)
    if tag2[1] == "/" and tag1[1] != "/":
        return (False,stri)
    if tag1[1] == "/" and tag2[1] != "/":
        return (True, tag1[:1] + tag1[2:] + tag1 + tag2 + tag2[:1] + "/" + tag2[1:])
    if tag1[1] == "/" and tag2[1] == "/":
        return (True, tag1[:1] + tag1[2:] + tag1 + tag2[:1] + tag2[2:] + tag2)
    if tag1[1] != "/" and tag2[1] != "/":
        return (True, tag1 + tag2 + tag2[:1] + "/" + tag2[1:] + tag1[:1] + "/" + tag1[1:] )






