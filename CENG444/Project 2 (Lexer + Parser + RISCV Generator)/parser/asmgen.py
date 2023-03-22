from ast_tools import Place, PlaceType
import struct
from utils import il_instr_to_str

# define double_to_hex (or float_to_hex)
def double_to_hex(f):
    return hex(struct.unpack('<Q', struct.pack('<d', f))[0])

def find_param(params, var_name, scope):
    # Assuming that scope != 'global
    for param in params[scope]:
        if param[0].val == var_name:
            return param
    return None

def find_local_var(places, var_name, scope):
    for var in places[scope]:
        if var.val == var_name:
            return var
    return None

class AssemblyGenerator:
    def __init__(self, relative_addr_table, stack_size, params, places):
        self.relative_addr_table = relative_addr_table
        self.sp_extra_offset = 0
        self.stack_size = stack_size
        self.label_cnt = 0
        self.cur_scope = 'global'
        self.params = params
        self.places = places
        self.param_regs = ['a0', 'a1', 'a2', 'a3', 'a4', 'a5', 'a6', 'a7']
        self.func_bodies = []

    def get_prologue(self, strings):

        asm = []
        # print(strings)
        if len(strings) > 0:
            asm.extend([f'  .data  # strings'])
            for string_temp in strings:
                string = strings[string_temp]
                asm.extend([f'{string_temp.val}:  .asciz "{string[1:-1]}"'])

        asm.extend([f'  .global main',
                    f'  .text',
                    f'  .align 2',
                    f'main:',
                    f'  addi sp, sp, -{self.stack_size}',
                    f'  sd ra, {self.stack_size-8}(sp)'])

        return '\n'.join(asm) + '\n'

    def get_epilogue(self, stack_size):
        asm = [f'  ld ra, {stack_size - 8}(sp)',
               f'  addi sp, sp, {stack_size}',
               f'  mv a0, zero',
               f'  ret']

        return '\n'.join(asm) + '\n'

    def get_func_decls(self):
        return '\n'.join(self.func_bodies) + '\n'

    def il_instr_to_asm(self, il_instr):
        if il_instr[0] == 'UMINUS':
            return self.UMINUS_to_asm(il_instr)
        elif il_instr[0] == '+':
            return self.ADD_to_asm(il_instr)
        elif il_instr[0] == '-':
            return self.SUBTRACT_to_asm(il_instr)
        elif il_instr[0] == '*':
            return self.MULTIPLY_to_asm(il_instr)
        elif il_instr[0] == '/':
            return self.DIVIDE_to_asm(il_instr)
        elif il_instr[0] == 'NOT':
            return self.NOT_to_asm(il_instr)
        elif il_instr[0] == 'COPY':
            return self.COPY_to_asm(il_instr)
        elif il_instr[0] == 'AND':
            return self.AND_to_asm(il_instr)
        elif il_instr[0] == 'OR':
            return self.OR_to_asm(il_instr)
        elif il_instr[0] == '<':
            return self.LESS_THAN_to_asm(il_instr)
        elif il_instr[0] == '>':
            return self.GREATER_THAN_to_asm(il_instr)
        elif il_instr[0] == '==':
            return self.EQUALS_to_asm(il_instr)
        elif il_instr[0] == '!=':
            return self.NOT_EQUALS_to_asm(il_instr)
        elif il_instr[0] == '<=':
            return self.LTE_to_asm(il_instr)
        elif il_instr[0] == '>=':
            return self.GTE_to_asm(il_instr)
        elif il_instr[0] == 'IFELSE':
            return self.IFELSE_to_asm(il_instr)
        elif il_instr[0] == 'WHILE':
            return self.WHILE_to_asm(il_instr)
        elif il_instr[0] == 'CALL':
            return self.CALL_to_asm(il_instr)
        elif il_instr[0] == 'FUN':
            return self.FUN_to_asm(il_instr)
        elif il_instr[0] == 'BLOCK':
            return self.BLOCK_to_asm(il_instr)
        elif il_instr[0] == '#':
            return self.HASH_to_asm(il_instr)
        elif il_instr[0] == 'RETURN':
            return self.RETURN_to_asm(il_instr)

    def MULTIPLY_to_asm(self, il_instr):
        # Handles type coercion
        # il_instr is of form ('*', place, left, right)
        # The overflooded resulting bytes after 8 bytes are ignored 
        
        # TODO: Does not handle parameter passing. However, it is very similar to ADD_to_asm
        # only that the addition functions need to be adjusted to multiplication
    
        dest = il_instr[1]
        left = il_instr[2]
        right = il_instr[3]
        dest_addr = self.addr(dest)
        
        asm = []

        valid_types = [PlaceType.Floating,
                       PlaceType.FloatingVariable,
                       PlaceType.Integer,
                       PlaceType.IntegerVariable]

        if left.type not in valid_types:
            print(f'Left operand {left} for multiplication does not have valid type') 
            exit()

        if right.type not in valid_types:
            print(f'Right operand {right} for multiplication does not have valid type') 
            exit()

        if left.type == PlaceType.Floating:
            dummy_addr = self.get_dummy_addr()
            if right.type == PlaceType.Floating:
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  fmul.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  fld f1, {right_addr}',
                            f'  fmul.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  fcvt.d.l f1, t1',
                            f'  fmul.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  ld t1, {right_addr}',
                            f'  fcvt.d.l f1, t1',
                            f'  fmul.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
        elif left.type == PlaceType.FloatingVariable:
            left_addr = self.addr(left)
            if right.type == PlaceType.Floating:
                dummy_addr = self.get_dummy_addr()
                asm.extend([f'  fld f0, {left_addr}',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  fmul.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  fld f0, {left_addr}',
                            f'  fld f1, {right_addr}',
                            f'  fmul.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  fld f0, {left_addr}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  fcvt.d.l f1, t1',
                            f'  fmul.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                right_addr = self.addr(right)
                asm.extend([f'  fld f0, {left_addr}',
                            f'  ld t1, {right_addr}',
                            f'  fcvt.d.l f1, t1',
                            f'  fmul.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
        elif left.type == PlaceType.Integer:
            if right.type == PlaceType.Floating:
                dummy_addr = self.get_dummy_addr()
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  fcvt.d.l f0, t0',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  fmul.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  fcvt.d.l f0, t0',
                            f'  fld f1, {right_addr}',
                            f'  fmul.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  mul t2, t0, t1',
                            f'  sd t2, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  ld t1, {right_addr}',
                            f'  mul t2, t0, t1',
                            f'  sd t2, {dest_addr}'])
        elif left.type == PlaceType.IntegerVariable:
            left_addr = self.addr(left)
            if right.type == PlaceType.Floating:
                dummy_addr = self.get_dummy_addr()
                asm.extend([f'  ld t0, {left_addr}',
                            f'  fcvt.d.l f0, t0',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  fmul.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  ld t0, {left_addr}',
                            f'  fcvt.d.l f0, t0',
                            f'  fld f1, {right_addr}',
                            f'  fmul.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  ld t0, {left_addr}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  mul t2, t0, t1',
                            f'  sd t2, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                right_addr = self.addr(right)
                asm.extend([f'  ld t0, {left_addr}',
                            f'  ld t1, {right_addr}',
                            f'  mul t2, t0, t1',
                            f'  sd t2, {dest_addr}'])
        
        return '\n'.join(asm) + '\n'

    def DIVIDE_to_asm(self, il_instr):
        # Handles type coercion
        # il_instr is of form ('/', place, left, right)
        # The overflooded resulting bytes after 8 bytes are ignored 

        # TODO: Does not handle parameter passing. However, it is very similar to ADD_to_asm
        # only that the addition functions need to be adjusted to divide functions
    
        dest = il_instr[1]
        left = il_instr[2]
        right = il_instr[3]
        dest_addr = self.addr(dest)
        
        asm = []

        valid_types = [PlaceType.Floating,
                       PlaceType.FloatingVariable,
                       PlaceType.Integer,
                       PlaceType.IntegerVariable]

        if left.type not in valid_types:
            print(f'Left operand {left} for multiplication does not have valid type') 
            exit()

        if right.type not in valid_types:
            print(f'Right operand {right} for multiplication does not have valid type') 
            exit()

        if left.type == PlaceType.Floating:
            dummy_addr = self.get_dummy_addr()
            if right.type == PlaceType.Floating:
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  fdiv.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  fld f1, {right_addr}',
                            f'  fdiv.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  fcvt.d.l f1, t1',
                            f'  fdiv.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  ld t1, {right_addr}',
                            f'  fcvt.d.l f1, t1',
                            f'  fdiv.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
        elif left.type == PlaceType.FloatingVariable:
            left_addr = self.addr(left)
            if right.type == PlaceType.Floating:
                dummy_addr = self.get_dummy_addr()
                asm.extend([f'  fld f0, {left_addr}',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  fdiv.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  fld f0, {left_addr}',
                            f'  fld f1, {right_addr}',
                            f'  fdiv.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  fld f0, {left_addr}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  fcvt.d.l f1, t1',
                            f'  fdiv.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                right_addr = self.addr(right)
                asm.extend([f'  fld f0, {left_addr}',
                            f'  ld t1, {right_addr}',
                            f'  fcvt.d.l f1, t1',
                            f'  fdiv.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
        elif left.type == PlaceType.Integer:
            if right.type == PlaceType.Floating:
                dummy_addr = self.get_dummy_addr()
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  fcvt.d.l f0, t0',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  fdiv.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  fcvt.d.l f0, t0',
                            f'  fld f1, {right_addr}',
                            f'  fdiv.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  div t2, t0, t1',
                            f'  sd t2, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  ld t1, {right_addr}',
                            f'  div t2, t0, t1',
                            f'  sd t2, {dest_addr}'])
        elif left.type == PlaceType.IntegerVariable:
            left_addr = self.addr(left)
            if right.type == PlaceType.Floating:
                dummy_addr = self.get_dummy_addr()
                asm.extend([f'  ld t0, {left_addr}',
                            f'  fcvt.d.l f0, t0',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  fdiv.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  ld t0, {left_addr}',
                            f'  fcvt.d.l f0, t0',
                            f'  fld f1, {right_addr}',
                            f'  fdiv.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  ld t0, {left_addr}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  div t2, t0, t1',
                            f'  sd t2, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                right_addr = self.addr(right)
                asm.extend([f'  ld t0, {left_addr}',
                            f'  ld t1, {right_addr}',
                            f'  div t2, t0, t1',
                            f'  sd t2, {dest_addr}'])
        
        return '\n'.join(asm) + '\n'

    def SUBTRACT_to_asm(self, il_instr):
        # Handles type coercion
        # il_instr is of form ('-', place, left, right)

        # TODO: Does not handle parameter passing. However, it is very similar to ADD_to_asm
        # only that the addition functions need to be adjusted to subtraction

        dest = il_instr[1]
        left = il_instr[2]
        right = il_instr[3]
        dest_addr = self.addr(dest)
        
        asm = []

        valid_types = [PlaceType.Floating,
                       PlaceType.FloatingVariable,
                       PlaceType.Integer,
                       PlaceType.IntegerVariable]

        if left.type not in valid_types:
            print(f'Left operand {left} for addition does not have valid type') 
            exit()

        if right.type not in valid_types:
            print(f'Right operand {right} for addition does not have valid type') 
            exit()

        if left.type == PlaceType.Floating:
            dummy_addr = self.get_dummy_addr()
            if right.type == PlaceType.Floating:
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  fneg.d f1, f1',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  fld f1, {right_addr}',
                            f'  fneg.d f1, f1',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  fcvt.d.l f1, t1',
                            f'  fneg.d f1, f1',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  ld t1, {right_addr}',
                            f'  fcvt.d.l f1, t1',
                            f'  fneg.d f1, f1',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
        elif left.type == PlaceType.FloatingVariable:
            left_addr = self.addr(left)
            if right.type == PlaceType.Floating:
                dummy_addr = self.get_dummy_addr()
                asm.extend([f'  fld f0, {left_addr}',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  fneg.d f1, f1',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  fld f0, {left_addr}',
                            f'  fld f1, {right_addr}',
                            f'  fneg.d f1, f1',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  fld f0, {left_addr}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  fcvt.d.l f1, t1',
                            f'  fneg.d f1, f1',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                right_addr = self.addr(right)
                asm.extend([f'  fld f0, {left_addr}',
                            f'  ld t1, {right_addr}',
                            f'  fcvt.d.l f1, t1',
                            f'  fneg.d f1, f1',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
        elif left.type == PlaceType.Integer:
            if right.type == PlaceType.Floating:
                dummy_addr = self.get_dummy_addr()
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  fcvt.d.l f0, t0',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  fneg.d f1, f1',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  fcvt.d.l f0, t0',
                            f'  fld f1, {right_addr}',
                            f'  fneg.d f1, f1',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  neg t1, t1',
                            f'  add t0, t0, t1',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  ld t1, {right_addr}',
                            f'  neg t1, t1',
                            f'  add t0, t0, t1',
                            f'  sd t0, {dest_addr}'])
        elif left.type == PlaceType.IntegerVariable:
            left_addr = self.addr(left)
            if right.type == PlaceType.Floating:
                dummy_addr = self.get_dummy_addr()
                asm.extend([f'  ld t0, {left_addr}',
                            f'  fcvt.d.l f0, t0',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  fneg.d f1, f1',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  ld t0, {left_addr}',
                            f'  fcvt.d.l f0, t0',
                            f'  fld f1, {right_addr}',
                            f'  fneg.d f1, f1',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  ld t0, {left_addr}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  neg t1, t1',
                            f'  add t0, t0, t1',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                right_addr = self.addr(right)
                asm.extend([f'  ld t0, {left_addr}',
                            f'  ld t1, {right_addr}',
                            f'  neg t1, t1',
                            f'  add t0, t0, t1',
                            f'  sd t0, {dest_addr}'])
        
        return '\n'.join(asm) + '\n'

    def ADD_to_asm(self, il_instr):
        # Handles type coercion
        # il_instr is of form ('+', place, left, right)

        dest = il_instr[1]
        left = il_instr[2]
        right = il_instr[3]
        dest_addr = self.addr(dest)
        
        asm = []

        valid_types = [PlaceType.Floating,
                       PlaceType.FloatingVariable,
                       PlaceType.Integer,
                       PlaceType.IntegerVariable]

        if left.type not in valid_types:
            print(f'Left operand {left} for addition does not have valid type') 
            exit()

        if right.type not in valid_types:
            print(f'Right operand {right} for addition does not have valid type') 
            exit()

        if left.type == PlaceType.Floating:
            dummy_addr = self.get_dummy_addr()
            if right.type == PlaceType.Floating:
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  fld f1, {right_addr}',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  fcvt.d.l f1, t1',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                var = find_local_var(self.places, right.val, self.cur_scope)
                if var:
                    right_addr = self.addr(var)
                    asm.extend([f'  li t0, {double_to_hex(left.val)}',
                                f'  sd t0, {dummy_addr}',
                                f'  fld f0, {dummy_addr}',
                                f'  ld t1, {right_addr}',
                                f'  fcvt.d.l f1, t1',
                                f'  fadd.d f0, f0, f1',
                                f'  fsd f0, {dest_addr}'])
                else:
                    param = None if self.cur_scope == 'global' else find_param(self.params, right.val, self.cur_scope)
                    if self.cur_scope != 'global' and param:
                        reg = param[1]
                        asm.extend([f'  li t0, {double_to_hex(left.val)}',
                                    f'  sd t0, {dummy_addr}',
                                    f'  fld f0, {dummy_addr}',
                                    f'  mv t1, {reg}',
                                    f'  fcvt.d.l f1, t1',
                                    f'  fadd.d f0, f0, f1',
                                    f'  fsd f0, {dest_addr}'])
        elif left.type == PlaceType.FloatingVariable:
            left_addr = self.addr(left)
            if right.type == PlaceType.Floating:
                dummy_addr = self.get_dummy_addr()
                asm.extend([f'  fld f0, {left_addr}',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  fld f0, {left_addr}',
                            f'  fld f1, {right_addr}',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  fld f0, {left_addr}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  fcvt.d.l f1, t1',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                var = find_local_var(self.places, right.val, self.cur_scope)
                if var:
                    right_addr = self.addr(var)
                    asm.extend([f'  fld f0, {left_addr}',
                                f'  ld t1, {right_addr}',
                                f'  fcvt.d.l f1, t1',
                                f'  fadd.d f0, f0, f1',
                                f'  fsd f0, {dest_addr}'])
                else:
                    param = None if self.cur_scope == 'global' else find_param(self.params, right.val, self.cur_scope)
                    if self.cur_scope != 'global' and param:
                        reg = param[1]
                        asm.extend([f'  fld f0, {left_addr}',
                                    f'  mv t1, {reg}',
                                    f'  fcvt.d.l f1, t1',
                                    f'  fadd.d f0, f0, f1',
                                    f'  fsd f0, {dest_addr}'])
        elif left.type == PlaceType.Integer:
            if right.type == PlaceType.Floating:
                dummy_addr = self.get_dummy_addr()
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  fcvt.d.l f0, t0',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  fcvt.d.l f0, t0',
                            f'  fld f1, {right_addr}',
                            f'  fadd.d f0, f0, f1',
                            f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  add t0, t0, t1',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                var = find_local_var(self.places, right.val, self.cur_scope)
                if var:
                    right_addr = self.addr(var)
                    asm.extend([f'  li t0, {hex(int(left.val))}',
                                f'  ld t1, {right_addr}',
                                f'  add t0, t0, t1',
                                f'  sd t0, {dest_addr}'])
                else:
                    param = None if self.cur_scope == 'global' else find_param(self.params, right.val, self.cur_scope)
                    if self.cur_scope != 'global' and param:
                        reg = param[1]
                        asm.extend([f'  li t0, {hex(int(left.val))}',
                                    f'  mv t1, {reg}',
                                    f'  add t0, t0, t1',
                                    f'  sd t0, {dest_addr}'])
        elif left.type == PlaceType.IntegerVariable:
            left_var = find_local_var(self.places, left.val, self.cur_scope)
            if right.type == PlaceType.Floating:
                dummy_addr = self.get_dummy_addr()
                if left_var:
                    left_addr = self.addr(left_var)
                    asm.extend([f'  ld t0, {left_addr}',
                                f'  fcvt.d.l f0, t0',
                                f'  li t1, {hex(int(right.val))}',
                                f'  sd t1, {dummy_addr}',
                                f'  fld f1, {dummy_addr}',
                                f'  fadd.d f0, f0, f1',
                                f'  fsd f0, {dest_addr}'])
                else:
                    param = None if self.cur_scope == 'global' else find_param(self.params, left.val, self.cur_scope)
                    if self.cur_scope != 'global' and param:
                        reg = param[1]
                        asm.extend([f'  mv t0, {reg}',
                                    f'  fcvt.d.l f0, t0',
                                    f'  li t1, {hex(int(right.val))}',
                                    f'  sd t1, {dummy_addr}',
                                    f'  fld f1, {dummy_addr}',
                                    f'  fadd.d f0, f0, f1',
                                    f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                if left_var:
                    left_addr = self.addr(left_var)
                    asm.extend([f'  ld t0, {left_addr}',
                                f'  fcvt.d.l f0, t0',
                                f'  fld f1, {right_addr}',
                                f'  fadd.d f0, f0, f1',
                                f'  fsd f0, {dest_addr}'])
                else:
                    param = None if self.cur_scope == 'global' else find_param(self.params, left.val, self.cur_scope)
                    if self.cur_scope != 'global' and param:
                        reg = param[1]
                        asm.extend([f'  mv t0, {reg}',
                                    f'  fcvt.d.l f0, t0',
                                    f'  fld f1, {right_addr}',
                                    f'  fadd.d f0, f0, f1',
                                    f'  fsd f0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                if left_var:
                    left_addr = self.addr(left_var)
                    asm.extend([f'  ld t0, {left_addr}',
                                f'  li t1, {hex(int(right.val))}',
                                f'  add t0, t0, t1',
                                f'  sd t0, {dest_addr}'])
                else:
                    param = None if self.cur_scope == 'global' else find_param(self.params, left.val, self.cur_scope)
                    if self.cur_scope != 'global' and param:
                        reg = param[1]
                        asm.extend([f'  mv t0, {reg}',
                                    f'  li t1, {hex(int(right.val))}',
                                    f'  add t0, t0, t1',
                                    f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                if left_var:
                    left_addr = self.addr(left_var)
                    right_var = find_local_var(self.places, right.val, self.cur_scope)
                    if right_var:
                        right_addr = self.addr(right_var)
                        asm.extend([f'  ld t0, {left_addr}',
                                    f'  ld t1, {right_addr}',
                                    f'  add t0, t0, t1',
                                    f'  sd t0, {dest_addr}'])
                    else:
                        param_right = None if self.cur_scope == 'global' else find_param(self.params, right.val, self.cur_scope)
                        if self.cur_scope != 'global' and param_right:
                            reg_right = param_right[1]
                            asm.extend([f'  ld t0, {left_addr}',
                                        f'  mv t1, {reg_right}',
                                        f'  add t0, t0, t1',
                                        f'  sd t0, {dest_addr}'])
                else:
                    param_left = None if self.cur_scope == 'global' else find_param(self.params, left.val, self.cur_scope)
                    if self.cur_scope != 'global' and param_left:
                        right_var = find_local_var(self.places, right.val, self.cur_scope)
                        if right_var:
                            right_addr = self.addr(right_var)
                            reg_left = param_left[1]
                            asm.extend([f'  mv t0, {reg_left}',
                                        f'  ld t1, {right_addr}',
                                        f'  add t0, t0, t1',
                                        f'  sd t0, {dest_addr}'])
                        else:
                            param_right = None if self.cur_scope == 'global' else find_param(self.params, right.val, self.cur_scope)
                            if self.cur_scope != 'global' and param_right:
                                reg_left = param_left[1]
                                reg_right = param_right[1]
                                asm.extend([f'  mv t0, {reg_left}',
                                            f'  mv t1, {reg_right}',
                                            f'  add t0, t0, t1',
                                            f'  sd t0, {dest_addr}'])
        
        return '\n'.join(asm) + '\n'

    def COPY_to_asm(self, il_instr):
        # ('COPY', place, expr['place'])
        # TODO: Implement vectors
        src = il_instr[2]
        dest = il_instr[1]
        dest_addr = self.addr(dest)
        asm = []

        # Literals
        if src.type == PlaceType.String:
            # TODO: Does not store the address correctly
            asm.extend([f'  la t0, {src.val}',
                        f'  sd t0, {dest_addr}'])
        elif src.type == PlaceType.Integer:
            asm.extend([f'  li t0, {hex(int(src.val))}',
                        f'  sd t0, {dest_addr}'])
        elif src.type == PlaceType.Floating:
            asm.extend([f'  li t0, {double_to_hex(src.val)}',
                        f'  sd t0, {dest_addr}'])
        elif src.type == PlaceType.Logical:
            val = 1 if src.val == True else 0
            asm.extend([f'  li t0, {val}',
                        f'  sd t0, {dest_addr}'])

        # Variables
        elif src.type == PlaceType.FloatingVariable:
            # Params do not support floats
            src_addr = self.addr(src)
            asm.extend([f'  fld f0, {src_addr}',
                        f'  fsd f0, {dest_addr}'])
        elif src.type == PlaceType.IntegerVariable:
            # if local var exists, get it
            # else, try to get param
            var = find_local_var(self.places, src.val, self.cur_scope)
            if var:
                src_addr = self.addr(src)
                asm.extend([f'  ld t0, {src_addr}',
                            f'  sd t0, {dest_addr}'])
            else:
                param = None if self.cur_scope == 'global' else find_param(self.params, src.val, self.cur_scope)
                if self.cur_scope != 'global' and param:
                    reg = param[1]
                    asm.extend([f'  mv t0, {reg}',
                                f'  sd t0, {dest_addr}'])                
        elif src.type == PlaceType.LogicalVariable:
            var = find_local_var(self.places, src.val, self.cur_scope)
            if var:
                src_addr = self.addr(src)
                asm.extend([f'  ld t0, {src_addr}',
                            f'  sd t0, {dest_addr}'])
            else:
                param = None if self.cur_scope == 'global' else find_param(self.params, src.val, self.cur_scope)
                if self.cur_scope != 'global' and param:
                    reg = param[1]
                    asm.extend([f'  mv t0, {reg}',
                                f'  sd t0, {dest_addr}'])                
        elif src.type == PlaceType.StringVariable:
            # TODO: The address is not stored correctly, so it can not fetch it
            # TODO: Implement parameter passing as well
            src_addr = self.addr(src)
            asm.extend([f'  ld t0, {src_addr}',
                        f'  sd t0, {dest_addr}'])
        elif src.type == PlaceType.EmptyVariable:
            print(f'An empty variable is trying to be assigned')
            exit()
        else:
            # Src is of type vector
            pass

        return '\n'.join(asm) + '\n'

    def UMINUS_to_asm(self, il_instr):
        # il_instr is of form ('AUMINUS', place, right)

        # TODO: Does not handle parameter passing. However, it is very similar to ADD_to_asm
        # only that the addition functions need to be adjusted to negation

        dest = il_instr[1]
        right = il_instr[2]
        dest_addr = self.addr(dest)

        asm = []

        valid_types = [PlaceType.Floating,
                       PlaceType.FloatingVariable,
                       PlaceType.Integer,
                       PlaceType.IntegerVariable]

        if right.type not in valid_types:
            print(f'The operand {right} for unary minus does not have valid type') 
            exit()

        if right.type == PlaceType.Floating:
            dummy_addr = self.get_dummy_addr()
            asm.extend([f'  li t0, {double_to_hex(right.val)}',
                        f'  sd t0, {dummy_addr}',
                        f'  fld f0, {dummy_addr}',
                        f'  fneg.d f0, f0',
                        f'  fsd f0, {dest_addr}'])
        elif right.type == PlaceType.FloatingVariable:
            right_addr = self.addr(right)
            asm.extend([f'  fld f0, {right_addr}',
                        f'  fneg.d f0, f0',
                        f'  fsd f0, {dest_addr}'])
        elif right.type == PlaceType.Integer:
            asm.extend([f'  li t0, {hex(int(right.val))}',
                        f'  neg t0, t0',
                        f'  sd t0, {dest_addr}'])
        elif right.type == PlaceType.IntegerVariable:
            right_addr = self.addr(right)
            asm.extend([f'  ld t0, {right_addr}',
                        f'  neg t0, t0',
                        f'  sd t0, {dest_addr}'])

        return '\n'.join(asm) + '\n'

    def AND_to_asm(self, il_instr):
        # Does short circuiting
        # il_insrt is of form ('AND', place, left, right)

        # TODO: Does not handle parameter passing. However, it is very similar to ADD_to_asm
        # only that the addition functions need to be adjusted to AND operations

        dest = il_instr[1]
        left = il_instr[2]
        right = il_instr[3]

        dest_addr = self.addr(dest)

        asm = []

        valid_types = [PlaceType.Logical,
                       PlaceType.LogicalVariable]

        if left.type not in valid_types:
            print(f'The operand {left} for AND does not have valid type') 
            exit()

        if right.type not in valid_types:
            print(f'The operand {right} for AND does not have valid type') 
            exit()

        labelx = self.generate_label()
        labely = self.generate_label()

        if left.type == PlaceType.Logical:
            left_val = 1 if left.val == True else 0
            if right.type == PlaceType.Logical:
                right_val = 1 if right.val == True else 0
                asm.extend([f'  li t0, {left_val}',
                            f'  bnez t0, {labelx}',
                            f'  li t0, {hex(int(0))}',
                            f'  sd t0, {dest_addr}',
                            f'  j {labely}',
                            f'{labelx}:',
                            f'  li t1, {right_val}',
                            f'  and t0, t0, t1',
                            f'  sd t0, {dest_addr}',
                            f'{labely}:'])
            elif right.type == PlaceType.LogicalVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {left_val}',
                            f'  bnez t0, {labelx}',
                            f'  li t0, {hex(int(0))}',
                            f'  sd t0, {dest_addr}',
                            f'  j {labely}',
                            f'{labelx}:',
                            f'  ld t1, {right_addr}',
                            f'  and t0, t0, t1',
                            f'  sd t0, {dest_addr}',
                            f'{labely}:'])
        elif left.type == PlaceType.LogicalVariable:
            left_addr = self.addr(left)
            if right.type == PlaceType.Logical:
                right_val = 1 if right.val == True else 0
                asm.extend([f'  ld t0, {left_addr}',
                            f'  bnez t0, {labelx}',
                            f'  li t0, {hex(int(0))}',
                            f'  sd t0, {dest_addr}',
                            f'  j {labely}',
                            f'{labelx}:',
                            f'  li t1, {right_val}',
                            f'  and t0, t0, t1',
                            f'  sd t0, {dest_addr}',
                            f'{labely}:'])
            elif right.type == PlaceType.LogicalVariable:
                right_addr = self.addr(right)
                asm.extend([f'  ld t0, {left_addr}',
                            f'  bnez t0, {labelx}',
                            f'  li t0, {hex(int(0))}',
                            f'  sd t0, {dest_addr}',
                            f'  j {labely}',
                            f'{labelx}:',
                            f'  ld t1, {right_addr}',
                            f'  and t0, t0, t1',
                            f'  sd t0, {dest_addr}',
                            f'{labely}:'])

        return '\n'.join(asm) + '\n'

    def OR_to_asm(self, il_instr):
        # Does short circuiting
        # il_insrt is of form ('OR', place, left, right)

        # TODO: Does not handle parameter passing. However, it is very similar to ADD_to_asm
        # only that the addition functions need to be adjusted to or operations

        dest = il_instr[1]
        left = il_instr[2]
        right = il_instr[3]

        dest_addr = self.addr(dest)

        asm = []

        valid_types = [PlaceType.Logical,
                       PlaceType.LogicalVariable]

        if left.type not in valid_types:
            print(f'The operand {left} for AND does not have valid type') 
            exit()

        if right.type not in valid_types:
            print(f'The operand {right} for AND does not have valid type') 
            exit()

        labelx = self.generate_label()
        labely = self.generate_label()

        if left.type == PlaceType.Logical:
            left_val = 1 if left.val == True else 0
            if right.type == PlaceType.Logical:
                right_val = 1 if right.val == True else 0
                asm.extend([f'  li t0, {left_val}',
                            f'  bnez t0, {labelx}',
                            f'  li t1, {right_val}',
                            f'  or t0, t0, t1',
                            f'  j {labely}',
                            f'{labelx}:',
                            f'  li t0, 1',
                            f'{labely}:',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.LogicalVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {left_val}',
                            f'  bnez t0, {labelx}',
                            f'  ld t1, {right_addr}',
                            f'  or t0, t0, t1',
                            f'  j {labely}',
                            f'{labelx}:',
                            f'  li t0, 1',
                            f'{labely}:',
                            f'  sd t0, {dest_addr}'])
        elif left.type == PlaceType.LogicalVariable:
            left_addr = self.addr(left)
            if right.type == PlaceType.Logical:
                right_val = 1 if right.val == True else 0
                asm.extend([f'  ld t0, {left_addr}',
                            f'  bnez t0, {labelx}',
                            f'  li t1, {right_val}',
                            f'  or t0, t0, t1',
                            f'  j {labely}',
                            f'{labelx}:',
                            f'  li t0, 1',
                            f'{labely}:',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.LogicalVariable:
                right_addr = self.addr(right)
                asm.extend([f'  ld t0, {left_addr}',
                            f'  bnez t0, {labelx}',
                            f'  ld t1, {right_addr}',
                            f'  or t0, t0, t1',
                            f'  j {labely}',
                            f'{labelx}:',
                            f'  li t0, 1',
                            f'{labely}:',
                            f'  sd t0, {dest_addr}'])

        return '\n'.join(asm) + '\n'

    def LESS_THAN_to_asm(self, il_instr):
        # Handles type coercion
        # il_instr is of form (comparison.op, place, left, right)

        # TODO: Does not handle parameter passing. However, it is very similar to ADD_to_asm
        # only that the addition functions need to be adjusted to less than operations

        dest = il_instr[1]
        left = il_instr[2]
        right = il_instr[3]
        dest_addr = self.addr(dest)
        
        asm = []

        valid_types = [PlaceType.Floating,
                       PlaceType.FloatingVariable,
                       PlaceType.Integer,
                       PlaceType.IntegerVariable]

        labelx = self.generate_label()
        labely = self.generate_label()

        if left.type not in valid_types:
            print(f'Left operand {left} for < does not have valid type') 
            exit()

        if right.type not in valid_types:
            print(f'Right operand {right} for < does not have valid type') 
            exit()

        if left.type == PlaceType.Floating:
            dummy_addr = self.get_dummy_addr()
            if right.type == PlaceType.Floating:
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  flt.d t0, f0, f1',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  fld f1, {right_addr}',
                            f'  flt.d t0, f0, f1',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  fcvt.d.l f1, t1',
                            f'  flt.d t0, f0, f1',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {double_to_hex(left.val)}',
                            f'  sd t0, {dummy_addr}',
                            f'  fld f0, {dummy_addr}',
                            f'  ld t1, {right_addr}',
                            f'  fcvt.d.l f1, t1',
                            f'  flt.d t0, f0, f1',
                            f'  sd t0, {dest_addr}'])
        elif left.type == PlaceType.FloatingVariable:
            left_addr = self.addr(left)
            if right.type == PlaceType.Floating:
                asm.extend([f'  fld f0, {left_addr}',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  flt.d t0, f0, f1',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  fld f0, {left_addr}',
                            f'  fld f1, {right_addr}',
                            f'  flt.d t0, f0, f1',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  fld f0, {left_addr}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  fcvt.d.l f1, t1',
                            f'  flt.d t0, f0, f1',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                right_addr = self.addr(right)
                asm.extend([f'  fld f0, {left_addr}',
                            f'  ld t1, {right_addr}',
                            f'  fcvt.d.l f1, t1',
                            f'  flt.d t0, f0, f1',
                            f'  sd t0, {dest_addr}'])
        elif left.type == PlaceType.Integer:
            if right.type == PlaceType.Floating:
                dummy_addr = self.get_dummy_addr()
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  fcvt.d.l f0, t0',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  flt.d t0, f0, f1',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  fcvt.d.l f0, t0',
                            f'  fld f1, {right_addr}',
                            f'  flt.d t0, f0, f1',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  bge t0, t1, {labelx}',
                            f'  li t0, 1',
                            f'  j {labely}',
                            f'{labelx}:',
                            f'  li t0, 0',
                            f'{labely}:',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                right_addr = self.addr(right)
                asm.extend([f'  li t0, {hex(int(left.val))}',
                            f'  ld t1, {right_addr}',
                            f'  bge t0, t1, {labelx}',
                            f'  li t0, 1',
                            f'  j {labely}',
                            f'{labelx}:',
                            f'  li t0, 0',
                            f'{labely}:',
                            f'  sd t0, {dest_addr}'])
        elif left.type == PlaceType.IntegerVariable:
            left_addr = self.addr(left)
            if right.type == PlaceType.Floating:
                dummy_addr = self.get_dummy_addr()
                asm.extend([f'  ld t0, {left_addr}',
                            f'  fcvt.d.l f0, t0',
                            f'  li t1, {double_to_hex(right.val)}',
                            f'  sd t1, {dummy_addr}',
                            f'  fld f1, {dummy_addr}',
                            f'  flt.d t0, f0, f1',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.FloatingVariable:
                right_addr = self.addr(right)
                asm.extend([f'  ld t0, {left_addr}',
                            f'  fcvt.d.l f0, t0',
                            f'  fld f1, {right_addr}',
                            f'  flt.d t0, f0, f1',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.Integer:
                asm.extend([f'  ld t0, {left_addr}',
                            f'  li t1, {hex(int(right.val))}',
                            f'  bge t0, t1, {labelx}',
                            f'  li t0, 1',
                            f'  j {labely}',
                            f'{labelx}:',
                            f'  li t0, 0',
                            f'{labely}:',
                            f'  sd t0, {dest_addr}'])
            elif right.type == PlaceType.IntegerVariable:
                right_addr = self.addr(right)
                asm.extend([f'  ld t0, {left_addr}',
                            f'  ld t1, {right_addr}',
                            f'  bge t0, t1, {labelx}',
                            f'  li t0, 1',
                            f'  j {labely}',
                            f'{labelx}:',
                            f'  li t0, 0',
                            f'{labely}:',
                            f'  sd t0, {dest_addr}'])

        return '\n'.join(asm) + '\n'

    def GREATER_THAN_to_asm(self, il_instr):
        # TODO: NOT IMPLEMENTED YET. But it is very similar to LESS_THAN_to_asm
        # except the < instructions need to be adjusted accordingly to > instructions
        pass

    def EQUALS_to_asm(self, il_instr):
        # TODO: NOT IMPLEMENTED YET. But it is very similar to LESS_THAN_to_asm
        # except the < instructions need to be adjusted accordingly to = instructions
        pass

    def NOT_EQUALS_to_asm(self, il_instr):
        # TODO: NOT IMPLEMENTED YET. But it is very similar to LESS_THAN_to_asm
        # except the < instructions need to be adjusted accordingly to != instructions
        pass

    def LTE_to_asm(self, il_instr):
        # TODO: NOT IMPLEMENTED YET. But it is very similar to LESS_THAN_to_asm
        # except the < instructions need to be adjusted accordingly to <= instructions
        pass

    def GTE_to_asm(self, il_instr):
        # TODO: NOT IMPLEMENTED YET. But it is very similar to LESS_THAN_to_asm
        # except the < instructions need to be adjusted accordingly to >= instructions
        pass

    def NOT_to_asm(self, il_instr):
        # TODO: NOT IMPLEMENTED YET. But it is very similar to UMINUS_to_asm
        # except the arithmetic negation instructions need to be adjusted accordingly to logical negation instructions
        pass

    def HASH_to_asm(self, il_instr):
        # TODO: NOT IMPLEMENTED YET.
        pass

    def IFELSE_to_asm(self, il_instr):
        # il_instr is of form ('IFELSE', cond, if_part, else_part)
        cond = il_instr[1]
        if_part = il_instr[2]
        else_part = il_instr[3]
        cond_result = cond['place']
        cond_result_addr = self.addr(cond_result)

        cond_code = ""
        if_code = ""
        else_code = ""

        for cond_instr in cond['code']:
            cond_code += self.il_instr_to_asm(cond_instr)

        for if_part_instr in if_part['code']:
            if_code += self.il_instr_to_asm(if_part_instr)

        for else_part_instr in else_part['code']:
            else_code += self.il_instr_to_asm(else_part_instr)

        asm = []

        labelx = self.generate_label()
        labely = self.generate_label()

        asm.extend([cond_code,
                    f'  ld t0, {cond_result_addr}',
                    f'  beqz t0, {labelx}',
                    if_code,
                    f'  j {labely}',
                    f'{labelx}:',
                    else_code,
                    f'{labely}:'])

        return '\n'.join(asm) + '\n'

    def WHILE_to_asm(self, il_instr):
        # il_instr is of form ('WHILE', cond, body)

        cond = il_instr[1]
        body = il_instr[2]
        cond_result = cond['place']
        cond_result_addr = self.addr(cond_result)

        cond_code = ""
        body_code = ""

        for cond_instr in cond['code']:
            cond_code += self.il_instr_to_asm(cond_instr)

        for body_instr in body['code']:
            body_code += self.il_instr_to_asm(body_instr)

        asm = []

        labelx = self.generate_label()
        labely = self.generate_label()

        asm.extend([f'{labelx}:',
                    cond_code,
                    f'  ld t0, {cond_result_addr}',
                    f'  beqz t0, {labely}',
                    body_code,
                    f'  j {labelx}',
                    f'{labely}:'])

        return '\n'.join(asm) + '\n'

    def BLOCK_to_asm(self, il_instr):
        # il_instr is of form ('BLOCK', var_decls, stmts)
        var_decls_body = ""
        stmts_body = ""
        var_decls = il_instr[1]
        stmts = il_instr[2]
        for var_decl in var_decls:
            for instr in var_decl:
                var_decls_body += self.il_instr_to_asm(instr)

        for stmt in stmts:
            for instr in stmt:
                stmts_body += self.il_instr_to_asm(instr)

        asm = []

        asm.extend([var_decls_body,
                    stmts_body])

        return '\n'.join(asm) + '\n'

    def CALL_to_asm(self, il_instr):
        # il_instr is of form ('CALL', place, arg_code, id)
        dest = il_instr[1]
        arg_instrs = il_instr[2]
        func_id = il_instr[3]

        # Handle the parameters
        arg_code = ""
        i = 0
        for arg_instr in arg_instrs:
            for instr in arg_instr['code']:
                arg_code += self.il_instr_to_asm(instr)
            arg_place = arg_instr['place']
            dest_reg = self.param_regs[i]

            if arg_place.type == PlaceType.Integer or arg_place.type == PlaceType.Logical:
                arg_code += f'  li t0, {hex(int(arg_place.val))} \n'
                arg_code += f'  mv {dest_reg}, t0 \n'
            elif arg_place.type == PlaceType.IntegerVariable or arg_place.type == PlaceType.LogicalVariable:
                src_addr = self.addr(arg_place)
                arg_code += f'  ld t0, {src_addr} \n'
                arg_code += f'  mv {dest_reg}, t0 \n'
            i += 1

        stack_size = len(self.places[func_id])*8+16
        dest_addr = self.addr(dest)

        asm = [arg_code,
               f'  mv t3, t0',
               f'  mv t4, t1',
               f'  mv t5, t2',
               f'  fmv.d f3, f0',
               f'  fmv.d f4, f1',
               f'  fmv.d f5, f2',
               f'  addi sp, sp, -{stack_size}',
               f'  call x1, .{func_id}',
               f'  sd a0, {dest_addr}']

        return '\n'.join(asm) + '\n'

    def FUN_to_asm(self, il_instr):
        # il_instr is of form ('FUN', id, body)
        id = il_instr[1]
        body = il_instr[2]
        self.cur_scope = id
        
        stack_size = len(self.places[self.cur_scope])*8+16
        self.sp_extra_offset += self.stack_size
        self.stack_size += stack_size

        body_code = ""
        for body_instr in body['code']:
            body_code += self.il_instr_to_asm(body_instr)

        stack_size = len(self.places[self.cur_scope])*8+16

        fun_asm = [f'.{id}:',
                   body_code,
                   f'  mv t0, t3',
                   f'  mv t1, t4',
                   f'  mv t2, t5',
                   f'  fmv.d f0, f3',
                   f'  fmv.d f1, f4',
                   f'  fmv.d f2, f5',
                   f'  addi sp, sp, {stack_size}',
                   f'  ret']

        self.sp_extra_offset -= stack_size
        self.stack_size -= stack_size
        self.cur_scope = 'global'

        self.func_bodies.append(f'            # {il_instr_to_str(il_instr)} \n' + '\n'.join(fun_asm) + '\n')
        return ""

    def RETURN_to_asm(self, il_instr):
        # il_instr is of form ('RETURN', expr)
        expr = il_instr[1]

        expr_code = ""
        for expr_instr in expr['code']:
            expr_code += self.il_instr_to_asm(expr_instr)
        expr_place = expr['place']

        # Only support int and logical returns
        param = find_param(self.params, expr_place.val, self.cur_scope)
        param_reg = None
        if param:
            # Returning param
            i = 0
            for candidate_param in self.params[self.cur_scope]:
                print(candidate_param, param)
                if candidate_param == param:
                    param_reg = self.param_regs[i]
                    break
        
            if param_reg:
                asm = [expr_code,
                        f'  mv a0, {param_reg}']
        else:
            if expr_place.type == PlaceType.LogicalVariable or expr_place.type == PlaceType.IntegerVariable:
                expr_place_addr = self.addr(expr_place)
                asm = [expr_code,
                        f'  ld t0, {expr_place_addr}',
                        f'  mv a0, t0']
            elif expr_place.type == PlaceType.Logical or expr_place.type == PlaceType.Integer:
                if expr_place.type == PlaceType.Logical:
                    value = 1 if expr_place.val == True else 0
                    asm = [expr_code,
                            f'  li t0, {hex(int(value))}',
                            f'  mv a0, t0']
                else:
                    asm = [expr_code,
                            f'  li t0, {hex(int(expr_place.val))}',
                            f'  mv a0, t0']

        return '\n'.join(asm) + '\n'

    def generate_label(self):
        label = '.label' + str(self.label_cnt)
        self.label_cnt += 1
        return label

    def addr(self, place):
        return str(self.relative_addr_table[self.cur_scope][place])+'(sp)'

    def get_dummy_addr(self):
        return str(f'{self.stack_size - 16}(sp)')