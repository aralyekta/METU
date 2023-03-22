  .global main
  .text
  .align 2
main:
  addi sp, sp, -32
  sd ra, 24(sp)
            # COPY {type:LogicalVariable, val: x}, {type:Logical, val: True}
  li t0, 1
  sd t0, 0(sp)
            # CALL {type:IntegerVariable, val: tmp1}, [{'place': {type:LogicalVariable, val: x}, 'code': []}], f1
  ld t0, 0(sp) 
  mv a0, t0 

  mv t3, t0
  mv t4, t1
  mv t5, t2
  fmv.d f3, f0
  fmv.d f4, f1
  fmv.d f5, f2
  addi sp, sp, -32
  call x1, .f1
  sd a0, 8(sp)
            # COPY {type:IntegerVariable, val: x}, {type:IntegerVariable, val: tmp1}
  ld t0, 8(sp)
  sd t0, 0(sp)
  ld ra, 24(sp)
  addi sp, sp, 32
  mv a0, zero
  ret
            # FUN f1, {'code': [('BLOCK', [[('COPY', {type:IntegerVariable, val: x}, {type:IntegerVariable, val: a})]], [[('IFELSE', {'place': {type:LogicalVariable, val: tmp0}, 'code': [('<', {type:LogicalVariable, val: tmp0}, {type:IntegerVariable, val: x}, {type:Integer, val: 2.0})]}, {'code': [('RETURN', {'place': {type:Integer, val: 1.0}, 'code': []})]}, {'code': [('RETURN', {'place': {type:Integer, val: 2.0}, 'code': []})]})]])]} 
.f1:
  mv t0, a0
  sd t0, 0(sp)

  ld t0, 0(sp)
  li t1, 0x2
  bge t0, t1, .label0
  li t0, 1
  j .label1
.label0:
  li t0, 0
.label1:
  sd t0, 8(sp)

  ld t0, 8(sp)
  beqz t0, .label2

  li t0, 0x1
  mv a0, t0

  j .label3
.label2:

  li t0, 0x2
  mv a0, t0

.label3:


  mv t0, t3
  mv t1, t4
  mv t2, t5
  fmv.d f0, f3
  fmv.d f1, f4
  fmv.d f2, f5
  addi sp, sp, 32
  ret

