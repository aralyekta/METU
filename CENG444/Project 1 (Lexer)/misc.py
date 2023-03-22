from ast_tools import *
from typing import List
from parser_1 import Parser
from lexer import Lexer


def process(source):
    # This will use lexer and parser
    '''parse the source text here. you may return the AST specified in ast_tools.py or something else.'''
    lexer = Lexer()
    parser = Parser()
    tokens = lexer.tokenize(source)
    res = parser.parse(tokens)
    return res


def generate_ast(intermediate) -> Program:
    '''return the AST using the output of process() here.'''
    queue = []
    varDecls = None
    funDecls = None
    freeStatements = None
    for elem in intermediate:
        queue.append(elem)
        if elem[0] == 'varDecls':
            varDecls = elem
        elif elem[0] == 'funDecls':
            funDecls = elem
        elif elem[0] == 'freeStatements':
            freeStatements = elem
        print(elem)

    root = Program(varDecls, funDecls, freeStatements)
    return root
    pass


def undeclared_vars(intermediate) -> List[Identifier]:
    '''return all of the undeclared uses of the variables in the order they appear in the source code here, using the return value of process()'''
    pass


def multiple_var_declarations(intermediate) -> List[Identifier]:
    '''return all of the subsequent declarations of a previously declared variable if the re-declaration cannot be explained by shadowing,
    in the order they appear in the source code, using the return value of process()'''
    pass
