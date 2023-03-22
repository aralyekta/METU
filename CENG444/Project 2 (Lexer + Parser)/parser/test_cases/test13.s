  .global main
  .text
  .align 2
main:
  addi sp, sp, -56
  sd ra, 48(sp)
            # COPY {type:IntegerVariable, val: x}, {type:Integer, val: 2.0}
  li t0, 0x2
  sd t0, 24(sp)
            # COPY {type:FloatingVariable, val: a}, {type:Floating, val: 2.3}
  li t0, 0x4002666666666666
  sd t0, 32(sp)
            # * {type:FloatingVariable, val: tmp0}, {'place': {type:IntegerVariable, val: x}}, {'place': {type:FloatingVariable, val: a}}
  ld t0, 24(sp)
  fcvt.d.l f0, t0
  fld f1, 32(sp)
  fmul.d f0, f0, f1
  fsd f0, 8(sp)
            # COPY {type:FloatingVariable, val: y}, {type:FloatingVariable, val: tmp0}
  fld f0, 8(sp)
  fsd f0, 16(sp)
            # COPY {type:FloatingVariable, val: z}, {type:FloatingVariable, val: y}
  fld f0, 16(sp)
  fsd f0, 0(sp)
  ld ra, 48(sp)
  addi sp, sp, 56
  mv a0, zero
  ret
