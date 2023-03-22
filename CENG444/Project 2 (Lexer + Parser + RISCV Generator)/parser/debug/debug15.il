places: {{type:IntegerVariable, val: z}, {type:IntegerVariable, val: tmp0}, {type:IntegerVariable, val: tmp2}, {type:IntegerVariable, val: y}, {type:IntegerVariable, val: tmp1}, {type:IntegerVariable, val: x}, {type:IntegerVariable, val: a}}

IL:
COPY {type:IntegerVariable, val: x}, {type:Integer, val: 2.0}
COPY {type:IntegerVariable, val: a}, {type:Integer, val: 2.0}
UMINUS {type:IntegerVariable, val: tmp0}, {type:IntegerVariable, val: x}
UMINUS {type:IntegerVariable, val: tmp1}, {type:IntegerVariable, val: a}
* {type:IntegerVariable, val: tmp2}, {'place': {type:IntegerVariable, val: tmp0}}, {'place': {type:IntegerVariable, val: tmp1}}
COPY {type:IntegerVariable, val: y}, {type:IntegerVariable, val: tmp2}
COPY {type:IntegerVariable, val: z}, {type:IntegerVariable, val: y}