stringo = raw_input()
instructo = raw_input()

righto = instructo.count(">")
lefto = instructo.count("<")
incremento = instructo.count("+")
discremento = instructo.count("-")

"""leftmost = righto - lefto
rightmost = righto
leftmost_ord = ord(stringo[leftmost])
#print leftmost_ord
leftmost_ord -= discremento
rightmost_ord = ord(stringo[rightmost])
#print rightmost_ord
rightmost_ord += incremento

new_stringo = stringo[:leftmost] + chr(leftmost_ord) + stringo[leftmost+3:rightmost] + chr(rightmost_ord) + stringo[rightmost+1:]
#print stringo[rightmost+1:]
print new_stringo"""

right_order = ord(stringo[righto])
right_order += incremento
new_char = chr(right_order)

lefto_new = righto - lefto
left_order = ord(stringo[lefto_new])
left_order -= discremento
new_char2 = chr(left_order)

#new_stringo = stringo[:righto] + new_char + stringo[righto+1:]
new_stringo = stringo[:lefto_new] + new_char2 + stringo[lefto_new+1:righto] + new_char + stringo[righto+1:]
print new_stringo
