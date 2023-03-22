import sly


class Lexer(sly.Lexer):
    tokens = {NUMBER, ID, WHILE, IF, ELSE, PRINT,
              PLUS, MINUS, TIMES, DIVIDE, ASSIGN,
              EQ, LT, LE, GT, GE, NE, AND,
              FALSE, TRUE, FUN, FOR, OR,
              RETURN, VAR, STRING, NOT, ERROR}

    # LE := <=
    # EQ := ==
    # LT := <
    # GT := >
    # GE := >=
    # NE := !=

    # Sanitize your tokens for the literals in the language (not token literals)!
    # each token t for NUMBER should have type(t.value) == float
    # each token t for STRING should have type(t.value) == str (remove the quotes!)
    # each token t for TRUE/FALSE should have type(t.value) == bool

    literals = {'(', ')', '{', '}', '[', ']', ';', ',', '#'}

    # Do not modify the sets Lexer.literals and Lexer.tokens!

    ignore = ' \t'
    ignore_comment = r'//[^\n]*'
    # ignore_newline = r'\n+'

    @_(r'//.*')
    def ignore_comment(self, t):
        return

    # Assuming that a string can be empty ("")
    @_(r'"[^"]*"')
    def STRING(self, t):
        t.value = t.value[1:-1]
        return t

    PLUS = r'\+'
    MINUS = r'-'
    TIMES = r'\*'
    DIVIDE = r'/'
    EQ = r'=='
    LE = r'<='
    GE = r'>='
    NE = r'!='
    ASSIGN = r'='
    LT = r'<'
    GT = r'>'

    @_(r'true(?![a-zA-Z0-9_]+)')
    def TRUE(self, t):
        t.value = True
        return t

    @_(r'false(?![a-zA-Z0-9_]+)')
    def FALSE(self, t):
        t.value = False
        return t

    ID = r'[a-zA-Z_][a-zA-Z0-9_]*'
    ID['while'] = WHILE
    ID['if'] = IF
    ID['else'] = ELSE
    ID['print'] = PRINT
    ID['and'] = AND
    ID['or'] = OR
    ID['return'] = RETURN
    ID['fun'] = FUN
    ID['for'] = FOR
    ID['var'] = VAR

    @_(r'\n+')
    def ignore_newline(self, t):
        self.lineno += t.value.count('\n')

    @_(r'[-+]?(\d+[.])?\d+')
    def NUMBER(self, t):
        t.value = float(t.value)
        return t

    @_(r'!')
    def NOT(self, t):
        t.value = '!'
        return t

    def error(self, t):
        # TODO: I may need to add logging here
        # Assuming the error is only for a single character
        self.index += 1
        t.value = t.value[0]
        return t
