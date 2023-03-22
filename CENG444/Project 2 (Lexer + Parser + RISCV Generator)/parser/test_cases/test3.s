  .global main
  .text
  .align 2
main:
  addi sp, sp, -16
  sd ra, 8(sp)
            # CALL {type:IntegerVariable, val: tmp0}, [{'place': {type:IntegerVariable, val: tmp1}, 'code': [('*', {type:IntegerVariable, val: tmp1}, {type:Integer, val: 2.0}, {type:Integer, val: 3.0})]}, {'place': {type:Integer, val: 5.0}, 'code': []}], f1
  li t0, 0x2
  li t1, 0x3
  mul t2, t0, t1
  sd t2, 16(sp)
  ld t0, 16(sp) 
  mv a0, t0 
  li t0, 0x5 
  mv a1, t0 

  mv t3, t0
  mv t4, t1
  mv t5, t2
  fmv.d f3, f0
  fmv.d f4, f1
  fmv.d f5, f2
  addi sp, sp, -16
  call x1, .f1
  sd a0, 8(sp)
            # COPY {type:IntegerVariable, val: x}, {type:IntegerVariable, val: tmp0}
  ld t0, 8(sp)
  sd t0, 0(sp)
  ld ra, 8(sp)
  addi sp, sp, 16
  mv a0, zero
  ret
            # FUN f1, {'code': [('BLOCK', [], [[('RETURN', {'place': {type:IntegerVariable, val: a}, 'code': []})]])]} 
.f1:


  mv a0, a0


  mv t0, t3
  mv t1, t4
  mv t2, t5
  fmv.d f0, f3
  fmv.d f1, f4
  fmv.d f2, f5
  addi sp, sp, 16
  ret

