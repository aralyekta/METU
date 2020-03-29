def ispalindr(stringo):
    if stringo == stringo[::-1]:
        return True
    else:
        return False

print ispalindr("ceng111")
print ispalindr("neveroddoreven")
