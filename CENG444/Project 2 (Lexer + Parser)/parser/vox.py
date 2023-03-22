import argparse
from misc import process, generate_ast
from ast_tools import ILVisitor
from asmgen import AssemblyGenerator
from utils import il_instr_to_str
import os

arg_parser = argparse.ArgumentParser()
arg_parser.add_argument('source_file')
arg_parser.add_argument('--save_il', action='store_true')
args = arg_parser.parse_args()

cur_dir = os.getcwd()
# output_dir = os.path.join(cur_dir, 'test_cases') 
# debug_dir = os.path.join(cur_dir, 'debug')

# asm_filename = os.path.join(output_dir, 'test' + str(i) + '.s')
# il_filename = os.path.join(debug_dir, 'debug' + str(i) + '.il')

src_file = os.path.join(cur_dir, args.source_file)
with open(src_file) as f:
  result = process(f.read())
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

  if(args.save_il):
    il_filename = os.path.join(cur_dir, args.source_file[:-4]+'.il')
    with open(il_filename, 'w') as f:
        f.write(f'places: {", ".join(places)}\n\nIL:\n')
        f.write('\n'.join([il_instr_to_str(il_instr) for il_instr in il]))


  relative_addr_table = dict()
  for scope in places:
    stack_size = len(places[scope])*8+16
    relative_addr_table[scope] = {place:addr for (place, addr) in zip(places[scope],range(0,stack_size-16,8))}

  asm_generator = AssemblyGenerator(relative_addr_table, stack_size, reg_mapped_params, places)
  asm_filename = os.path.join(cur_dir, args.source_file[:-4] + '.s')

  with open(asm_filename, 'w') as asm_file:
    prologue = asm_generator.get_prologue(strings)
    epilogue = asm_generator.get_epilogue(stack_size)

    asm_file.write(prologue)

    for il_instr in il:
      if il_instr[0] != 'FUN':
        asm_file.write('            # ' + il_instr_to_str(il_instr)+'\n')
      asm_file.write(asm_generator.il_instr_to_asm(il_instr))
    
    asm_file.write(epilogue)
    func_bodies = asm_generator.get_func_decls()
    asm_file.write(func_bodies)