places: {'global': {{type:IntegerVariable, val: x}, {type:IntegerVariable, val: tmp0}, {type:IntegerVariable, val: tmp1}}, 'f1': set()}

IL:
FUN f1, {'code': [('BLOCK', [], [[('RETURN', {'place': {type:IntegerVariable, val: a}, 'code': []})]])]}
CALL {type:IntegerVariable, val: tmp0}, [{'place': {type:IntegerVariable, val: tmp1}, 'code': [('*', {type:IntegerVariable, val: tmp1}, {type:Integer, val: 2.0}, {type:Integer, val: 3.0})]}, {'place': {type:Integer, val: 5.0}, 'code': []}], f1
COPY {type:IntegerVariable, val: x}, {type:IntegerVariable, val: tmp0}