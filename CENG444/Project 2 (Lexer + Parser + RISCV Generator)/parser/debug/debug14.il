places: {{type:IntegerVariable, val: z}, {type:IntegerVariable, val: tmp0}, {type:IntegerVariable, val: y}, {type:IntegerVariable, val: tmp1}, {type:IntegerVariable, val: x}}

IL:
COPY {type:IntegerVariable, val: x}, {type:Integer, val: 2.0}
UMINUS {type:IntegerVariable, val: tmp0}, {type:Integer, val: 2.0}
* {type:IntegerVariable, val: tmp1}, {'place': {type:IntegerVariable, val: x}}, {'place': {type:IntegerVariable, val: tmp0}}
COPY {type:IntegerVariable, val: y}, {type:IntegerVariable, val: tmp1}
COPY {type:IntegerVariable, val: z}, {type:IntegerVariable, val: y}