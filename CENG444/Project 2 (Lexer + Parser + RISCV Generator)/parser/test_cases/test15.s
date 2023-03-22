  .global main
  .text
  .align 2
main:
  addi sp, sp, -72
  sd ra, 64(sp)
            # COPY {type:IntegerVariable, val: x}, {type:Integer, val: 2.0}
  li t0, 0x2
  sd t0, 40(sp)
            # COPY {type:IntegerVariable, val: a}, {type:Integer, val: 2.0}
  li t0, 0x2
  sd t0, 48(sp)
            # UMINUS {type:IntegerVariable, val: tmp0}, {type:IntegerVariable, val: x}
  ld t0, 40(sp)
  neg t0, t0
  sd t0, 8(sp)
            # UMINUS {type:IntegerVariable, val: tmp1}, {type:IntegerVariable, val: a}
  ld t0, 48(sp)
  neg t0, t0
  sd t0, 32(sp)
            # * {type:IntegerVariable, val: tmp2}, {'place': {type:IntegerVariable, val: tmp0}}, {'place': {type:IntegerVariable, val: tmp1}}
  ld t0, 8(sp)
  ld t1, 32(sp)
  mul t2, t0, t1
  sd t2, 16(sp)
            # COPY {type:IntegerVariable, val: y}, {type:IntegerVariable, val: tmp2}
  ld t0, 16(sp)
  sd t0, 24(sp)
            # COPY {type:IntegerVariable, val: z}, {type:IntegerVariable, val: y}
  ld t0, 24(sp)
  sd t0, 0(sp)
  ld ra, 64(sp)
  addi sp, sp, 72
  mv a0, zero
  ret
