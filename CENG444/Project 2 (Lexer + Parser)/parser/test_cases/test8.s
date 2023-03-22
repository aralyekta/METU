  .global main
  .text
  .align 2
main:
  addi sp, sp, -40
  sd ra, 32(sp)
            # * {type:FloatingVariable, val: tmp0}, {'place': {type:Integer, val: 2.0}}, {'place': {type:Floating, val: 2.3}}
  li t0, 0x2
  fcvt.d.l f0, t0
  li t1, 0x4002666666666666
  sd t1, 24(sp)
  fld f1, 24(sp)
  fmul.d f0, f0, f1
  fsd f0, 8(sp)
            # COPY {type:FloatingVariable, val: y}, {type:FloatingVariable, val: tmp0}
  fld f0, 8(sp)
  fsd f0, 16(sp)
            # COPY {type:FloatingVariable, val: z}, {type:FloatingVariable, val: y}
  fld f0, 16(sp)
  fsd f0, 0(sp)
  ld ra, 32(sp)
  addi sp, sp, 40
  mv a0, zero
  ret
