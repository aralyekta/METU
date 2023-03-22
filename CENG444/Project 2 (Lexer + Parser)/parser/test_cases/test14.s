  .global main
  .text
  .align 2
main:
  addi sp, sp, -56
  sd ra, 48(sp)
            # COPY {type:IntegerVariable, val: x}, {type:Integer, val: 2.0}
  li t0, 0x2
  sd t0, 32(sp)
            # UMINUS {type:IntegerVariable, val: tmp0}, {type:Integer, val: 2.0}
  li t0, 0x2
  neg t0, t0
  sd t0, 8(sp)
            # * {type:IntegerVariable, val: tmp1}, {'place': {type:IntegerVariable, val: x}}, {'place': {type:IntegerVariable, val: tmp0}}
  ld t0, 32(sp)
  ld t1, 8(sp)
  mul t2, t0, t1
  sd t2, 24(sp)
            # COPY {type:IntegerVariable, val: y}, {type:IntegerVariable, val: tmp1}
  ld t0, 24(sp)
  sd t0, 16(sp)
            # COPY {type:IntegerVariable, val: z}, {type:IntegerVariable, val: y}
  ld t0, 16(sp)
  sd t0, 0(sp)
  ld ra, 48(sp)
  addi sp, sp, 56
  mv a0, zero
  ret
