  .global main
  .text
  .align 2
main:
  addi sp, sp, -40
  sd ra, 32(sp)
            # COPY {type:IntegerVariable, val: y}, {type:Integer, val: 1.0}
  li t0, 0x1
  sd t0, 0(sp)
            # IFELSE {'place': {type:LogicalVariable, val: tmp2}, 'code': [('<', {type:LogicalVariable, val: tmp2}, {type:IntegerVariable, val: y}, {type:Integer, val: 2.0})]}, {'place': {type:IntegerVariable, val: y}, 'code': [('CALL', {type:IntegerVariable, val: tmp3}, [{'place': {type:Integer, val: 1.0}, 'code': []}, {'place': {type:Integer, val: 1.0}, 'code': []}], 'f1'), ('COPY', {type:IntegerVariable, val: y}, {type:IntegerVariable, val: tmp3})]}, {'place': {type:IntegerVariable, val: y}, 'code': [('CALL', {type:IntegerVariable, val: tmp4}, [{'place': {type:Integer, val: 1.0}, 'code': []}, {'place': {type:Integer, val: 2.0}, 'code': []}], 'f1'), ('COPY', {type:IntegerVariable, val: y}, {type:IntegerVariable, val: tmp4})]}
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
  li t0, 0x1 
  mv a1, t0 

  mv t3, t0
  mv t4, t1
  mv t5, t2
  fmv.d f3, f0
  fmv.d f4, f1
  fmv.d f5, f2
  addi sp, sp, -40
  call x1, .f1
  sd a0, 24(sp)
  ld t0, 24(sp)
  sd t0, 0(sp)

  j .label3
.label2:
  li t0, 0x1 
  mv a0, t0 
  li t0, 0x2 
  mv a1, t0 

  mv t3, t0
  mv t4, t1
  mv t5, t2
  fmv.d f3, f0
  fmv.d f4, f1
  fmv.d f5, f2
  addi sp, sp, -40
  call x1, .f1
  sd a0, 32(sp)
  ld t0, 32(sp)
  sd t0, 0(sp)

.label3:
            # * {type:IntegerVariable, val: tmp5}, {type:IntegerVariable, val: y}, {type:Integer, val: 3.0}
  ld t0, 0(sp)
  li t1, 0x3
  mul t2, t0, t1
  sd t2, 16(sp)
            # COPY {type:IntegerVariable, val: y}, {type:IntegerVariable, val: tmp5}
  ld t0, 16(sp)
  sd t0, 0(sp)
  ld ra, 32(sp)
  addi sp, sp, 40
  mv a0, zero
  ret
            # FUN f1, {'code': [('BLOCK', [[('+', {type:IntegerVariable, val: tmp0}, {type:IntegerVariable, val: a}, {type:IntegerVariable, val: b}), ('COPY', {type:IntegerVariable, val: c}, {type:IntegerVariable, val: tmp0})]], [[('RETURN', {'place': {type:IntegerVariable, val: tmp1}, 'code': [('*', {type:IntegerVariable, val: tmp1}, {type:IntegerVariable, val: c}, {type:Integer, val: 2.0})]})]])]} 
.f1:
  mv t0, a0
  mv t1, a1
  add t0, t0, t1
  sd t0, 0(sp)
  ld t0, 0(sp)
  sd t0, 16(sp)

  ld t0, 16(sp)
  li t1, 0x2
  mul t2, t0, t1
  sd t2, 8(sp)

  ld t0, 8(sp)
  mv a0, t0


  mv t0, t3
  mv t1, t4
  mv t2, t5
  fmv.d f0, f3
  fmv.d f1, f4
  fmv.d f2, f5
  addi sp, sp, 40
  ret

