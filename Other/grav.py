rep = raw_input()
#m1_unit = "M"
m1 = rep.count('M')
#dist_unit = "-"
dist = rep.count('-')
#m2_unit = "m"
m2 = rep.count('m')
a = float(m1*m2)
b = float(dist ** 2)
force = a/b
print force
