import sly
import lexer


class Parser(sly.Parser):
    tokens = lexer.Lexer.tokens
    debugfile = 'parser.out'

    precedence = (
        ('left', 'ASSIGN'),
        ('left', 'AND'),
        ('left', 'OR'),
        ('left', 'PLUS', 'MINUS'),
        ('left', 'TIMES', 'DIVIDE'),
        ('right', 'UMINUS'),
    )

    # @_('varDecls funDecls freeStatements EOF')
    @_('',  # This may be wrong
       'varDecls',
       'funDecls',
       'freeStatements',
       'varDecls funDecls',
       'varDecls freeStatements',
       'funDecls freeStatements',
       'varDecls funDecls freeStatements')
    def program(self, p):
        # print("Program")
        return p

    @_('funDecl funDecls',
       'funDecl')
    def funDecls(self, p):
        # print("funDecls")
        return p

    @_('FUN function')
    def funDecl(self, p):
        # print("funDecl")
        return p

    @_('ID "(" ")" block',
       'ID "(" parameters ")" block')
    def function(self, p):
        # print("function")
        return p

    @_('IDs')
    def parameters(self, p):
        # print("parameters")
        return p

    @_('ID "," IDs',
       'ID')
    def IDs(self, p):
        # print("IDs")
        return p

    @_('"{" varDecls statements "}"',
       '"{" statements "}"',
       '"{" varDecls "}"',
       '"{" "}"')
    def block(self, p):
        # print("block")
        return p

    @_('statement statements',
       'statement')
    def statements(self, p):
        # print("statements")
        return p

    @_('freeStatement',
       'block')
    def statement(self, p):
        # print("statement")
        return p

    @_('varDecl varDecls',
       'varDecl')
    def varDecls(self, p):
        # print("varDecls")
        return p

    @_('VAR ID ";"',
       'VAR ID ASSIGN init ";"')
    def varDecl(self, p):
        # print("varDecl")
        return p

    @_('expr',
       '"[" exprs "]"')
    def init(self, p):
        # print("init")
        return p

    @_('freeStatement freeStatements',
       'freeStatement')
    def freeStatements(self, p):
        # print("freeStatements")
        return p

    @_('simpleStmt ";"',
       'compoundStmt')
    def freeStatement(self, p):
        # print("freeStatement")
        return p

    @_('ifStmt',
       'whileStmt',
       'forStmt')
    def compoundStmt(self, p):
        # print("compoundStmt")
        return p

    @_('IF lexpr statement',
       'IF lexpr statement ELSE statement')
    def ifStmt(self, p):
        # print("ifStmt")
        return p

    @_('WHILE lexpr statement')
    def whileStmt(self, p):
        # print("whileStmt")
        return p

    @_('FOR "(" ";" ";" ")" statement',
       'FOR "(" asgnStmt ";" ";" ")" statement',
       'FOR "(" ";" lexpr ";" ")" statement',
       'FOR "(" ";" ";" asgnStmt ")" statement',
       'FOR "(" asgnStmt ";" lexpr ";" ")" statement',
       'FOR "(" ";" lexpr ";" asgnStmt ")" statement',
       'FOR "(" asgnStmt ";" ";" asgnStmt ")" statement',
       'FOR "(" asgnStmt ";" lexpr ";" asgnStmt ")" statement'
       )
    def forStmt(self, p):
        # print("forStmt")
        return p

    @_('asgnStmt',
       'printStmt',
       'returnStmt')
    def simpleStmt(self, p):
        # print("simpleStmt")
        return p

    @_('ID ASSIGN expr',
       'ID "[" aexpr "]" ASSIGN expr')
    def asgnStmt(self, p):
        # print("asgnStmt")
        return p

    @_('PRINT expr')
    def printStmt(self, p):
        # print("printStmt")
        return p

    @_('RETURN expr')
    def returnStmt(self, p):
        # print("returnStmt")
        return p

    @_('lexpr',
       'aexpr',
       'sexpr')
    def expr(self, p):
        # print("expr")
        return p

    @_('aexpr NE aexpr',
       'aexpr EQ aexpr',
       'aexpr GT aexpr',
       'aexpr GE aexpr',
       'aexpr LT aexpr',
       'aexpr LE aexpr')
    def cexpr(self, p):
        # print("cexpr")
        return p

    @_('aexpr MINUS term',
       'aexpr PLUS term',
       'term')
    def aexpr(self, p):
        # print("aexpr")
        return p

    @_('lexpr OR lterm')
    def lexpr(self, p):
        # print("lexpr")
        return p

    @_('lterm AND lfact',
       'lfact')
    def lterm(self, p):
        # print("lterm")
        return p

    @_('"#" ID "[" aexpr "]"',
       '"#" ID',
       'cexpr',
       '"#" call',
       'NOT lfact %prec UMINUS',
       '"(" lexpr ")"')
    def lfact(self, p):
        # print("lfact")
        return p

    @_('expr',
       'expr "," exprs')
    def exprs(self, p):
        # print("exprs")
        return p

    @_('exprs')
    def arguments(self, p):
        # print("arguments")
        return p

    @_('ID "(" arguments ")"',
       'ID "(" ")"')
    def call(self, p):
        # print(p[0])
        return p

    @_('term DIVIDE fact',
       'term TIMES fact',
       'fact')
    def term(self, p):
        # print("term")
        return p

    @_('MINUS fact %prec UMINUS',
       'call',
       'NUMBER',
       '"(" aexpr ")"',
       'ID',
       'ID "[" aexpr "]"')
    def fact(self, p):
        # print("fact")
        return p

    @_('lterm')
    def lexpr(self, p):
        # print("lexpr")
        return p

    @_('STRING')
    def sexpr(self, p):
        # print("sexpr")
        return p

    @_('FALSE',
       'TRUE')
    def lfact(self, p):
        # print("lfact")
        return p

    # def error(self, tok):
    #     if not tok:
    #         # print("EOF")
    #         return
    #     # Read until ";" or "}"
    #     while True:
    #         tok = next(self.tokens, None)
    #         # if not tok or tok.type == 'SEMI' or tok.type == 'RBRACE' or tok.type == '':
    #         if not tok or tok == ';' or tok == '}' or tok == ')':
    #             break
    #         self.errok()

    #     # print("Error")

    #     # Continue with reading from ";" or "}"
    #     return tok
