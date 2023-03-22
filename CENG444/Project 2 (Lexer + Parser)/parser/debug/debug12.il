places: {{type:FloatingVariable, val: z}, {type:IntegerVariable, val: x}, {type:FloatingVariable, val: tmp0}, {type:FloatingVariable, val: y}}

IL:
COPY {type:IntegerVariable, val: x}, {type:Integer, val: 2.0}
* {type:FloatingVariable, val: tmp0}, {'place': {type:IntegerVariable, val: x}}, {'place': {type:Floating, val: 2.3}}
COPY {type:FloatingVariable, val: y}, {type:FloatingVariable, val: tmp0}
COPY {type:FloatingVariable, val: z}, {type:FloatingVariable, val: y}