places: {'global': {{type:IntegerVariable, val: tmp6}, {type:IntegerVariable, val: y}, {type:IntegerVariable, val: tmp2}, {type:IntegerVariable, val: tmp5}, {type:IntegerVariable, val: tmp3}, {type:IntegerVariable, val: tmp4}}, 'f1': {{type:IntegerVariable, val: tmp0}, {type:IntegerVariable, val: tmp1}, {type:IntegerVariable, val: c}}, 'f2': set()}

IL:
COPY {type:IntegerVariable, val: y}, {type:Integer, val: 2.0}
FUN f1, {'code': [('BLOCK', [[('+', {type:IntegerVariable, val: tmp0}, {type:IntegerVariable, val: a}, {type:IntegerVariable, val: b}), ('COPY', {type:IntegerVariable, val: c}, {type:IntegerVariable, val: tmp0})]], [[('RETURN', {'place': {type:IntegerVariable, val: tmp1}, 'code': [('*', {type:IntegerVariable, val: tmp1}, {type:IntegerVariable, val: c}, {type:Integer, val: 2.0})]})]])]}
FUN f2, {'code': [('BLOCK', [], [[('RETURN', {'place': {type:Logical, val: True}, 'code': []})]])]}
CALL {type:IntegerVariable, val: tmp2}, [{'place': {type:IntegerVariable, val: tmp5}, 'code': [('CALL', {type:IntegerVariable, val: tmp3}, [], 'f2'), ('*', {type:IntegerVariable, val: tmp4}, {type:IntegerVariable, val: tmp3}, {type:Integer, val: 5.0}), ('/', {type:IntegerVariable, val: tmp5}, {type:IntegerVariable, val: tmp4}, {type:Integer, val: 2.0})]}, {'place': {type:Integer, val: 3.0}, 'code': []}], f1
* {type:IntegerVariable, val: tmp6}, {type:IntegerVariable, val: tmp2}, {type:IntegerVariable, val: y}
COPY {type:IntegerVariable, val: y}, {type:IntegerVariable, val: tmp6}