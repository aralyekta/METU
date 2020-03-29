def power_derivative(term_str,der_var):
    var = term_str[:term_str.find("^")]
    exp = term_str[term_str.find("^")+1:]
    if not der_var == var:
        return 0
    if exp.isdigit():
        if int(exp) == 0:
            return 0
        if int(exp) == 2:
            return exp + var
        elif int(exp) == 1:
            return exp
        else:
            return exp + var + "^" + str((int(exp)-1))
    elif not exp.isdigit():
        return exp + var + "^" + "(" + exp + "-1" + ")"

print power_derivative("elma^5", "armut")
print power_derivative('elma^5','elma')
print power_derivative('x^5','y')
print power_derivative('x^1','x')
print power_derivative('a^b','a')
print power_derivative('a^0','a')
