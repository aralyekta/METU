  .global main
  .text
  .align 2
main:
  addi sp, sp, -32
  sd ra, 24(sp)
            # < {type:LogicalVariable, val: tmp0}, {type:Floating, val: 1.2}, {type:Integer, val: 2.0}
  li t0, 0x3ff3333333333333
  sd t0, 16(sp)
  fld f0, 16(sp)
  li t1, 0x2
  fcvt.d.l f1, t1
  flt.d t0, f0, f1
  sd t0, 8(sp)
            # COPY {type:LogicalVariable, val: y}, {type:LogicalVariable, val: tmp0}
  ld t0, 8(sp)
  sd t0, 0(sp)
  ld ra, 24(sp)
  addi sp, sp, 32
  mv a0, zero
  ret
