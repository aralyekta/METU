places: {{type:IntegerVariable, val: z}, {type:IntegerVariable, val: a}, {type:IntegerVariable, val: tmp0}, {type:IntegerVariable, val: y}}

IL:
COPY {type:IntegerVariable, val: a}, {type:Integer, val: 2.0}
* {type:IntegerVariable, val: tmp0}, {'place': {type:Integer, val: 3.0}}, {'place': {type:IntegerVariable, val: a}}
COPY {type:IntegerVariable, val: y}, {type:IntegerVariable, val: tmp0}
COPY {type:IntegerVariable, val: z}, {type:IntegerVariable, val: y}