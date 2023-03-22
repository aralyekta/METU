  .global main
  .text
  .align 2
main:
  addi sp, sp, -56
  sd ra, 48(sp)
            # CALL {type:IntegerVariable, val: tmp4}, [{'place': {type:Integer, val: 2.0}, 'code': []}], fac
  li t0, 0x2 
  mv a0, t0 

  mv t3, t0
  mv t4, t1
  mv t5, t2
  fmv.d f3, f0
  fmv.d f4, f1
  fmv.d f5, f2
  addi sp, sp, -56
  call x1, .fac
  sd a0, 8(sp)
            # COPY {type:IntegerVariable, val: res}, {type:IntegerVariable, val: tmp4}
  ld t0, 8(sp)
  sd t0, 0(sp)
  ld ra, 48(sp)
  addi sp, sp, 56
  mv a0, zero
  ret
            # FUN fac, {'code': [('BLOCK', [[('COPY', {type:IntegerVariable, val: x}, {type:IntegerVariable, val: x})]], [[('IFELSE', {'place': {type:LogicalVariable, val: tmp0}, 'code': [('<', {type:LogicalVariable, val: tmp0}, {type:IntegerVariable, val: x}, {type:Integer, val: 1.0})]}, {'code': [('RETURN', {'place': {type:Integer, val: 1.0}, 'code': []})]}, {'code': [('RETURN', {'place': {type:IntegerVariable, val: tmp3}, 'code': [('CALL', {type:IntegerVariable, val: tmp1}, [{'place': {type:IntegerVariable, val: tmp2}, 'code': [('-', {type:IntegerVariable, val: tmp2}, {type:IntegerVariable, val: x}, {type:Integer, val: 1.0})]}], 'fac'), ('*', {type:IntegerVariable, val: tmp3}, {type:IntegerVariable, val: x}, {type:IntegerVariable, val: tmp1})]})]})]])]} 
.fac:
  ld t0, 32(sp)
  sd t0, 32(sp)

  ld t0, 32(sp)
  li t1, 0x1
  bge t0, t1, .label0
  li t0, 1
  j .label1
.label0:
  li t0, 0
.label1:
  sd t0, 24(sp)

  ld t0, 24(sp)
  beqz t0, .label2

  li t0, 0x1
  mv a0, t0

  j .label3
.label2:
  ld t0, 32(sp)
  li t1, 0x1
  neg t1, t1
  add t0, t0, t1
  sd t0, 16(sp)
  ld t0, 16(sp) 
  mv a0, t0 

  mv t3, t0
  mv t4, t1
  mv t5, t2
  fmv.d f3, f0
  fmv.d f4, f1
  fmv.d f5, f2
  addi sp, sp, -56
  call x1, .fac
  sd a0, 0(sp)
  ld t0, 32(sp)
  ld t1, 0(sp)
  mul t2, t0, t1
  sd t2, 8(sp)

  ld t0, 8(sp)
  mv a0, t0

.label3:


  mv t0, t3
  mv t1, t4
  mv t2, t5
  fmv.d f0, f3
  fmv.d f1, f4
  fmv.d f2, f5
  addi sp, sp, 56
  ret

