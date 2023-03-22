  .global main
  .text
  .align 2
main:
  addi sp, sp, -40
  sd ra, 32(sp)
            # * {type:IntegerVariable, val: tmp0}, {'place': {type:Integer, val: 3435973836.0}}, {'place': {type:Integer, val: 54975581388.0}}
  li t0, 0xcccccccc
  li t1, 0xccccccccc
  mul t2, t0, t1
  sd t2, 8(sp)
            # COPY {type:IntegerVariable, val: y}, {type:IntegerVariable, val: tmp0}
  ld t0, 8(sp)
  sd t0, 16(sp)
            # COPY {type:IntegerVariable, val: z}, {type:IntegerVariable, val: y}
  ld t0, 16(sp)
  sd t0, 0(sp)
  ld ra, 32(sp)
  addi sp, sp, 40
  mv a0, zero
  ret
