def il_instr_to_str(il_instr):
    return il_instr[0]+" "+", ".join([str(elem) for elem in il_instr[1:] if elem is not None])