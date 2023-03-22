  .global main
  .text
  .align 2
main:
  addi sp, sp, -48
  sd ra, 40(sp)
            # COPY {type:IntegerVariable, val: x}, {type:Integer, val: 2.0}
  li t0, 0x2
  sd t0, 8(sp)
            # * {type:FloatingVariable, val: tmp0}, {'place': {type:IntegerVariable, val: x}}, {'place': {type:Floating, val: 2.3}}
  ld t0, 8(sp)
  fcvt.d.l f0, t0
  li t1, 0x4002666666666666
  sd t1, 32(sp)
  fld f1, 32(sp)
  fmul.d f0, f0, f1
  fsd f0, 16(sp)
            # COPY {type:FloatingVariable, val: y}, {type:FloatingVariable, val: tmp0}
  fld f0, 16(sp)
  fsd f0, 24(sp)
            # COPY {type:FloatingVariable, val: z}, {type:FloatingVariable, val: y}
  fld f0, 24(sp)
  fsd f0, 0(sp)
  ld ra, 40(sp)
  addi sp, sp, 48
  mv a0, zero
  ret
