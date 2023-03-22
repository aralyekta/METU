from lexer import Lexer
from misc import process, generate_ast
from ast_tools import ILVisitor
from asmgen import AssemblyGenerator
from utils import il_instr_to_str
import os

if __name__ == '__main__':

    gen_test1 = 'var z = "asdasd"; var x; z = 2; x = z + 2;'
    gen_test2 = 'var x = true;'
    gen_test3 = 'var z = 2; var x; z = "asd"; z = 3.3; z = true; x = z;'
    gen_test4 = 'var z = 2.2; var x = z;'
    gen_test5 = 'var z = 2.2; var x = z; z = 2; x = z; x = "123123";'
    gen_test6 = '''var x = "123this_is_a_too_long
    _string_really_long_i_mean_it_could_extend_to_a_second_line_meaning_it_would_have_a_newline_which_may_disrupt_the_label_mechanism"; '''
    
    test_case0 = '''var x = -2.2 * 3.2; var z = x;'''
    test_case1 = '''var x = 3.2; var y = -2.2 * -x; var z = y;'''
    test_case2 = '''var y = 2.2 * -2; var z = y;'''
    test_case3 = '''var x = 2; var y = 2.2 * x; var z = y;'''

    test_case4 = '''var x = 2.2; var y = x * 2.3; var z = y;'''
    test_case5 = '''var x = 2.2; var a = 2.3; var y = x * a; var z = y;'''
    test_case6 = '''var x = 2.2; var y = -x * 2; var z = y;'''
    test_case7 = '''var x = 2.2; var a = 2; var y = x * a; var z = y;'''

    test_case8 = '''var y = 2 * 2.3; var z = y;'''
    test_case9 = '''var a = 2.3; var y = 2 * a; var z = y;'''
    test_case10 = '''var y = 3435973836 * 54975581388; var z = y;'''
    test_case11 = '''var a = 2; var y = 3 * a; var z = y;'''

    test_case12 = '''var x = 2; var y = x * 2.3; var z = y;'''
    test_case13 = '''var x = 2; var a = 2.3; var y = x * a; var z = y;'''
    test_case14 = '''var x = 2; var y = x * -2; var z = y;'''
    test_case15 = '''var x = 2; var a = 2; var y = -x * -a; var z = y;'''

    # test_cases = [test_case0, test_case1, test_case2, test_case3,
    #               test_case4, test_case5, test_case6, test_case7,
    #               test_case8, test_case9, test_case10, test_case11,
    #               test_case12, test_case13, test_case14, test_case15]

    neg_case0 = '''var x = -2.2; var y = x;'''
    neg_case1 = '''var x = 2.2; var y = -x; var z = y;'''
    neg_case2 = '''var x = -2; var y = x;'''
    neg_case3 = '''var x = 2; var y = -x; var z = y;'''

    # test_cases = [neg_case0, neg_case1, neg_case2, neg_case3]

    and_case0 = '''var x = true and false;'''
    and_case1 = '''var x = false and false;'''
    and_case2 = '''var x = true and true;'''
    and_case3 = '''var x = false and true;'''
    
    and_case4 = '''var x = true; var y = #x and false;'''
    and_case5 = '''var x = true; var y = #x and true;'''
    and_case6 = '''var x = true; var y = true and #x;'''
    and_case7 = '''var x = true; var y = false and #x;'''

    and_case8 = '''var x = false; var y = #x and false;'''
    and_case9 = '''var x = false; var y = #x and true;'''
    and_case10 = '''var x = false; var y = true and #x;'''
    and_case11 = '''var x = false; var y = false and #x;'''

    and_case12 = '''var x = false; var y = #x and and false and #x;'''
    and_case13 = '''var x = false; var y = #x and true and #x;'''
    and_case14 = '''var x = true; var y = true and #x and #x;'''
    and_case15 = '''var x = false; var y = false and #x and #x;'''
    and_case16 = '''var x = false; var y = true and true and false;'''

    # test_cases = [and_case16]

    lt_case0 = '''var x = 1.2 < 2.2;'''
    lt_case1 = '''var x = 2.2 < 1.2;'''
    lt_case2 = '''var x = 1.2; var y = 2.2 < x;'''
    lt_case3 = '''var x = 2.2; var y = 1.2 < x;'''
    
    lt_case4 = '''var x = 2; var y = 1.2 < x;'''
    lt_case5 = '''var x = 2; var y = 2.2 < x;'''
    lt_case6 = '''var y = 2.2 < 2;'''
    lt_case7 = '''var y = 1.2 < 2;'''

    lt_case8 = '''var x = 2.2; var y = x < 2;'''
    lt_case9 = '''var x = 2.2; var y = x < 3;'''
    lt_case10 = '''var x = 2 < 3;'''
    lt_case11 = '''var x = 3 < 2;'''

    lt_case12 = '''var x = 2; var y = 1 < x;'''
    lt_case13 = '''var x = 2; var y = 3 < x;'''
    lt_case14 = '''var x = 2 < 3.2;'''
    lt_case15 = '''var x = 2; var y = x < 3;'''

    # test_cases = [lt_case14, lt_case15]

    ifelse_case0 = '''var x; if 2 < 3 * 2 x = 3 * 2.2; else x = 3;'''
    ifelse_case1 = '''var x; if 3 < 2 x = 3; else x = 2;'''
    ifelse_case2 = '''var x; if 2 < 3 if 1 < 2 x = 1; else x = 2; else x = 3;'''
    ifelse_case3 = '''var x; if 2 < 3 x = 2;'''

    ifelse_case4 = '''var x; if 2 < 3 if 2 < 1 x = 1; else x = 2; else x = 3;'''
    ifelse_case5 = '''var x; if 3 < 2 if 1 < 2 x = 1; else x = 2;'''

    add_case0 = '''var x = 1 + 2 + 3;'''

    # test_cases = [ifelse_case0, ifelse_case1, ifelse_case2, ifelse_case3,
    #               ifelse_case4, ifelse_case5]

    while_case0 = '''var x = 1; while x < 3 * 2.2 x = x + 1;'''
    while_case1 = '''var x = 1; while x < 3 * 2.2 {var y = 2; x = x + 1;}'''

    # test_cases = [while_case0]

    block_case0 = '''var x; var y = -5; fun f(x, a, b){var a = 2; var y = x + a; var z = 2 + x; var d = a + 3; var ab = a + y + z + d; return ab;} x = f(2,3,4) + 2; x = x - y;'''
    block_case1 = '''var x; fun f1(){return 1 + 2;} x = f1();'''
    block_case2 = '''var x = 0;fun f1(x){var a = x + 2;}'''
    block_case3 = '''var x = 0;fun f1(x){var x = 2; var a = x + 3;}'''
    block_case4 = '''var a = 2; fun f1(x){if x < 1 x = x + 1;} a = f1(0);'''  # Has a problem as conditionals do not support parameter passing yet 

    or_case0 = '''var x = true or false;'''
    or_case1 = '''var x = false or true;'''
    or_case2 = '''var x = false or false;'''

    subtraction_case0 = '''var x = 2; var y = x - 2.2;'''
    subtraction_case1 = '''var x = 2; var y = x - 3;'''

    div_case0 = '''var x = 3; var y = x/2;'''
    div_case1 = '''var x = 3; var y = 4.3/3;'''

    # test_cases = [block_case0]

    case0 = '''var x = 1; var y = 2; fun f1(a, b){var c = a + b; return c * 2;} fun f2(){return 2;} y = f2() + x * y;'''
    case1 = '''var x = 1; var y = 2; fun f1(a, b){var c = a + b; return c * 2;} fun f2(){return true;} y = f2() + x * y;'''
    case2 = '''var x = 1; var y = 2; fun f1(a, b){var c = a + b; return c * 2;} fun f2(){return true;} y = f1(f2(), 3) * y;'''
    case3 = '''var x; fun f1(a, b) {return a;} x = f1(2*3, 5);'''
    case4 = '''var x; fun f1(a) {var x = a; if x < 2 return 1; else return 2;} x = f1(true);'''  # Using x directly does not work as it is not implemented yet
    case5 = '''var x = true; fun f1(a) {var x = a; if x < 2 return 1; else return 2;} x = f1(x);'''  # Using x directly does not work as it is not implemented yet

    # test_cases = [case0, case1, case2, case3, case4, case5]

    case6 = '''var y = 2; fun f1(a, b){var c = a + b; return c * 2;} fun f2(){return true;} y = f1(f2() * 5 / 2, 3) * y;'''
    case7 = '''var y = 1; fun f1(a, b){var c = a + b; return c * 2;} if y < 2 y = f1(1,1); else y = f1(1,2); y = y * 3;'''
    case8 = '''var y = 2; fun f1(a, b){var x = a; var y = b; if x < y return true; else return false;} if y < 2 y = f1(1,2); else y = f1(2,1);'''
    
    test_cases = [case6, case7, case8]

    for i, test_case in enumerate(test_cases):

      cur_dir = os.getcwd()
      output_dir = os.path.join(cur_dir, 'test_cases') 
      debug_dir = os.path.join(cur_dir, 'debug')

      asm_filename = os.path.join(output_dir, 'test' + str(i) + '.s')
      il_filename = os.path.join(debug_dir, 'debug' + str(i) + '.il')

      result = process(test_case)
      ast = generate_ast(result)
      # print(ast)
      visitor = ILVisitor()
      il = visitor.visit(ast)
      
      places = visitor.places
      strings = visitor.strings
      params = visitor.params

      arg_regs = ['a0', 'a1', 'a2', 'a3', 'a4', 'a5', 'a6', 'a7']
      
      reg_mapped_params = {}
      for key in params:
        reg_mapped_params[key] = list(zip(params[key], arg_regs))

      print(reg_mapped_params)

      # print(res)
      # il = visitor.il
      print(places)
      print()
      print(params)

      # print(places)

      with open(il_filename, 'w') as f:
        f.write(f'places: {str(places)}\n\nIL:\n')
        f.write('\n'.join([il_instr_to_str(il_instr) for il_instr in il]))
      
      relative_addr_table = dict()
      for scope in places:
        stack_size = len(places[scope])*8+16
        relative_addr_table[scope] = {place:addr for (place, addr) in zip(places[scope],range(0,stack_size-16,8))}
      # relative_addr_table = {place:addr for (place, addr) in zip(places,range(0,stack_size-16,8))}
      print(relative_addr_table)

      asm_generator = AssemblyGenerator(relative_addr_table, stack_size, reg_mapped_params, places)

      with open(asm_filename, 'w') as asm_file:
        prologue = asm_generator.get_prologue(strings)
        epilogue = asm_generator.get_epilogue(stack_size)

        asm_file.write(prologue)

        # print(il)
        for il_instr in il:
          if il_instr[0] != 'FUN':
            asm_file.write('            # ' + il_instr_to_str(il_instr)+'\n')
          asm_file.write(asm_generator.il_instr_to_asm(il_instr))
        
        asm_file.write(epilogue)
        func_bodies = asm_generator.get_func_decls()
        asm_file.write(func_bodies)
