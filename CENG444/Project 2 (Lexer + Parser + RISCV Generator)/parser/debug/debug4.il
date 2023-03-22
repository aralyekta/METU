places: {'global': {{type:IntegerVariable, val: x}, {type:IntegerVariable, val: tmp1}}, 'f1': {{type:IntegerVariable, val: x}, {type:LogicalVariable, val: tmp0}}}

IL:
FUN f1, {'code': [('BLOCK', [[('COPY', {type:IntegerVariable, val: x}, {type:IntegerVariable, val: a})]], [[('IFELSE', {'place': {type:LogicalVariable, val: tmp0}, 'code': [('<', {type:LogicalVariable, val: tmp0}, {type:IntegerVariable, val: x}, {type:Integer, val: 2.0})]}, {'code': [('RETURN', {'place': {type:Integer, val: 1.0}, 'code': []})]}, {'code': [('RETURN', {'place': {type:Integer, val: 2.0}, 'code': []})]})]])]}
CALL {type:IntegerVariable, val: tmp1}, [{'place': {type:Logical, val: True}, 'code': []}], f1
COPY {type:IntegerVariable, val: x}, {type:IntegerVariable, val: tmp1}