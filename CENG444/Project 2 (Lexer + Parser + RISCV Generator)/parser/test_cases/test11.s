  .global main
  .text
  .align 2
main:
  addi sp, sp, -48
  sd ra, 40(sp)
            # COPY {type:IntegerVariable, val: a}, {type:Integer, val: 2.0}
  li t0, 0x2
  sd t0, 8(sp)
            # * {type:IntegerVariable, val: tmp0}, {'place': {type:Integer, val: 3.0}}, {'place': {type:IntegerVariable, val: a}}
  li t0, 0x3
  ld t1, 8(sp)
  mul t2, t0, t1
  sd t2, 16(sp)
            # COPY {type:IntegerVariable, val: y}, {type:IntegerVariable, val: tmp0}
  ld t0, 16(sp)
  sd t0, 24(sp)
            # COPY {type:IntegerVariable, val: z}, {type:IntegerVariable, val: y}
  ld t0, 24(sp)
  sd t0, 0(sp)
  ld ra, 40(sp)
  addi sp, sp, 48
  mv a0, zero
  ret
