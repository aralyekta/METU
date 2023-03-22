from __future__ import annotations
from dataclasses import dataclass
from abc import ABC, abstractmethod
from typing import List, Union
from enum import Enum

@dataclass(frozen=True)
class ASTNode:
    pass

@dataclass(frozen=True)
class Expr(ASTNode):
    '''expressions. some of the the parse tree components are not explicitly represented (such as parantheses to increase precedence)'''
    pass

@dataclass(frozen=True)
class LExpr(Expr):
    '''logical expressions. conditions of if/while/for stmts, operands of logical operators, and primaries prepended with # are members.'''
    pass

@dataclass(frozen=True)
class AExpr(Expr):
    '''arithmetic expressions.'''
    pass

@dataclass(frozen=True)
class SLiteral(Expr):
    '''string literal. the grammar makes them unusable in arithmetic/logical ops when they are expressed as naked string literals.'''
    value: str 

@dataclass(frozen=True)
class Stmt(ASTNode):
    '''statements. middle classes of statements (simpleStmt/free-statement etc.) are not explicitly represented.'''
    pass

@dataclass(frozen=True)
class ErrorStmt(Stmt):
    '''this node should correspond to an error during parsing that is resolved with character re-synchronization.'''
    pass

@dataclass(frozen=True)
class Decl(ASTNode):
    '''declarations.'''
    pass

@dataclass(frozen=True)
class Identifier:
    '''represents an identifier token. lineno and index fields are added to help with error reporting.'''
    name: str
    lineno: int
    index: int

@dataclass(frozen=True)
class VarDecl(Decl):
    '''variable declaration. the initilializer attribute is None if the variable is not initialized to any value,
    it is a list if the variable is initialized as a vector, and and Expr if it is initialized as a non-vector.'''
    identifier: Identifier
    initializer: Union[Expr, List[Expr], None]

@dataclass(frozen=True)
class FunDecl(Decl):
    '''function declaration. as in fun identifier(params...) body'''
    identifier: Identifier
    params: List[Identifier]
    body: Block

@dataclass(frozen=True)
class Program(ASTNode):
    '''the root node of the AST.'''
    var_decls: List[VarDecl]
    fun_decls: List[FunDecl]
    statements: List[Stmt]

@dataclass(frozen=True)
class Assign(Stmt):
    '''assignments to a variable in the form identifier = expr'''
    identifier: Identifier
    expr: Expr

@dataclass(frozen=True)
class SetVector(Stmt):
    '''assignments to a member of vector in the form identifier[vector_index] = expr'''
    identifier: Identifier
    vector_index: AExpr
    expr: Expr

@dataclass(frozen=True)
class ForLoop(Stmt):
    '''a for loop. If any of the fields are left empty, such as in for(;;){}, set them as None.'''
    initializer: Union[Assign, None]
    condition: Union[LExpr, None]
    increment: Union[Assign, None]
    body: Stmt

@dataclass(frozen=True)
class Return(Stmt):
    expr: Expr

@dataclass(frozen=True)
class WhileLoop(Stmt):
    condition: LExpr
    body: Stmt

@dataclass(frozen=True)
class Block(Stmt):
    var_decls: List[VarDecl]
    statements: List[Stmt]

@dataclass(frozen=True)
class Print(Stmt):
    expr: Expr

@dataclass(frozen=True)
class IfElse(Stmt):
    '''an if-else statement. If there is no else corresponding to this if, set else_branch as None.'''
    condition: LExpr
    if_branch: Stmt
    else_branch: Union[Stmt, None]

@dataclass(frozen=True)
class LBinary(LExpr):
    '''logical binary operations and and or. Set op as "and"/"or".'''
    op: str
    left: LExpr
    right: LExpr

@dataclass(frozen=True)
class Comparison(LExpr):
    '''comparison operations <,>,==,!=,<=,>=. Set op as "<"/">"/"=="/"!="/"<="/">=".'''
    op: str
    left: AExpr
    right: AExpr

@dataclass(frozen=True)
class LLiteral(LExpr):
    '''logical literals (TRUE/FALSE tokens).'''
    value: bool

@dataclass(frozen=True)
class LPrimary(LExpr):
    '''# operator on primaries: function calls(# fizzbuzz()), vector accesses(# foo[0]) or variables (# bar) to cast them explicitly as logical.'''
    primary: Union[Call, GetVector, Variable]

@dataclass(frozen=True)
class GetVector(AExpr):
    '''vector access as an expression, as in foo = identifier[vector_index]'''
    identifier: Identifier
    vector_index: AExpr

@dataclass(frozen=True)
class Variable(AExpr):
    '''variable access as an expression, as in foo = identifier'''
    identifier: Identifier

@dataclass(frozen=True)
class LNot(LExpr):
    '''! operation.'''
    right: LExpr

@dataclass(frozen=True)
class ABinary(AExpr):
    '''arithmetic binary operations +,-,* or /. Set op as "+"/"-"/"*" or "/"'''
    op: str
    left: AExpr
    right: AExpr

@dataclass(frozen=True)
class AUMinus(AExpr):
    '''unary minus operation'''
    right: AExpr

@dataclass(frozen=True)
class ALiteral(AExpr):
    '''arithmetic literals (Number)'''
    value: float

@dataclass(frozen=True)
class Call(AExpr):
    '''function call as an expression, as in foo = callee(arguments...)'''
    callee: Identifier
    arguments: List[Expr]

#https://stackoverflow.com/questions/11154668/is-the-visitor-pattern-useful-for-dynamically-typed-languages
class ASTNodeVisitor(ABC):
    def __init__(self):
        self.ASTNodes = {
            SLiteral: self.visit_SLiteral,
            Program : self.visit_Program,
            ErrorStmt: self.visit_ErrorStmt,
            VarDecl: self.visit_VarDecl,
            FunDecl: self.visit_FunDecl,
            Assign: self.visit_Assign,
            SetVector: self.visit_SetVector,
            ForLoop: self.visit_ForLoop,
            Return: self.visit_Return,
            WhileLoop: self.visit_WhileLoop,
            Block: self.visit_Block,
            Print: self.visit_Print,
            IfElse: self.visit_IfElse,
            LBinary: self.visit_LBinary,
            Comparison: self.visit_Comparison,
            LLiteral: self.visit_LLiteral,
            LPrimary: self.visit_LPrimary,
            GetVector: self.visit_GetVector,
            Variable: self.visit_Variable,
            LNot: self.visit_LNot,
            ABinary: self.visit_ABinary,
            AUMinus: self.visit_AUMinus,
            ALiteral: self.visit_ALiteral,
            Call: self.visit_Call
        }

    def visit(self, ast_node: ASTNode):
        return self.ASTNodes[type(ast_node)](ast_node)

    @abstractmethod
    def visit_SLiteral(self, sliteral: SLiteral):
        pass

    @abstractmethod
    def visit_Program(self, program: Program):
        pass

    @abstractmethod
    def visit_ErrorStmt(self, errorstmt: ErrorStmt):
        pass

    @abstractmethod
    def visit_VarDecl(self, vardecl: VarDecl):
        pass

    @abstractmethod
    def visit_FunDecl(self, fundecl: FunDecl):
        pass

    @abstractmethod
    def visit_Assign(self, assign: Assign):
        pass

    @abstractmethod
    def visit_SetVector(self, setvector: SetVector):
        pass

    @abstractmethod
    def visit_ForLoop(self, forloop: ForLoop):
        pass

    @abstractmethod
    def visit_Return(self, returnn: Return):
        pass

    @abstractmethod
    def visit_WhileLoop(self, whileloop: WhileLoop):
        pass

    @abstractmethod
    def visit_Block(self, block: Block):
        pass

    @abstractmethod
    def visit_Print(self, printt: Print):
        pass

    @abstractmethod
    def visit_IfElse(self, ifelse: IfElse):
        pass

    @abstractmethod
    def visit_LBinary(self, lbinary: LBinary):
        pass

    @abstractmethod
    def visit_Comparison(self, comparison: Comparison):
        pass

    @abstractmethod
    def visit_LLiteral(self, lliteral: LLiteral):
        pass

    @abstractmethod
    def visit_LPrimary(self, lprimary: LPrimary):
        pass

    @abstractmethod
    def visit_GetVector(self, getvector: GetVector):
        pass

    @abstractmethod
    def visit_Variable(self, variable: Variable):
        pass

    @abstractmethod
    def visit_LNot(self, lnot: LNot):
        pass

    @abstractmethod
    def visit_ABinary(self, abinary: ABinary):
        pass

    @abstractmethod
    def visit_AUMinus(self, auminus: AUMinus):
        pass

    @abstractmethod
    def visit_ALiteral(self, aliteral: ALiteral):
        pass

    @abstractmethod
    def visit_Call(self, calll: Call):
        pass

class PrintVisitor(ASTNodeVisitor):
    def indent(self, strr):
        return '\n'.join(['    '+elem for elem in strr.split('\n')])

    def visit_SLiteral(self, sliteral: SLiteral):
        return f'"{sliteral.value}"'

    def visit_Program(self, program: Program):
        return '\n'.join(["TOP_LVL VAR_DECLS:",
                '\n'.join([self.visit(elem) for elem in program.var_decls]),
                "TOP_LVL FUN_DECLS:",
                '\n'.join([self.visit(elem) for elem in program.fun_decls]),
                "TOP_LVL STMTS:",
                '\n'.join([self.visit(elem) for elem in program.statements])])

    def visit_ErrorStmt(self, errorstmt: ErrorStmt):
        return 'ERROR_STMT;'

    def visit_VarDecl(self, vardecl: VarDecl):
        if vardecl.initializer is None:
            return f"var {vardecl.identifier.name};"
        elif type(vardecl.initializer) == list:
            return f"var {vardecl.identifier.name} = [{', '.join([self.visit(elem) for elem in vardecl.initializer])}];"
        else:
            return f"var {vardecl.identifier.name} = {self.visit(vardecl.initializer)};"

    def visit_FunDecl(self, fundecl: FunDecl):
        return f"fun {fundecl.identifier.name}({', '.join([elem.name for elem in fundecl.params])}){self.visit(fundecl.body)}"

    def visit_Assign(self, assign: Assign):
        return f"{assign.identifier.name} = {self.visit(assign.expr)};"

    def visit_SetVector(self, setvector: SetVector):
        return f"{setvector.identifier.name}[{self.visit(setvector.vector_index)}] = {self.visit(setvector.expr)};"

    def visit_ForLoop(self, forloop: ForLoop):
        initializer = '' if forloop.initializer is None else self.visit(forloop.initializer)[:-1]
        condition = '' if forloop.condition is None else self.visit(forloop.condition)
        increment = '' if forloop.increment is None else self.visit(forloop.increment)[:-1]
        return f"for ({initializer};{condition};{increment}) {self.visit(forloop.body)}"

    def visit_Return(self, returnn: Return):
        return f"return {self.visit(returnn.expr)};"

    def visit_WhileLoop(self, whileloop: WhileLoop):
        return f"while {self.visit(whileloop.condition)} {self.visit(whileloop.body)}"

    def visit_Block(self, block: Block):
        return '\n'.join(['{',
                '  VAR_DECLS:',
                '\n'.join(["    "+self.visit(elem) for elem in block.var_decls]),
                '  STMTS:',
                '\n'.join([self.indent(self.visit(elem)) for elem in block.statements]),
                '}'])

    def visit_Print(self, printt: Print):
        return f"print {self.visit(printt.expr)};"

    def visit_IfElse(self, ifelse: IfElse):
        else_branch = '' if ifelse.else_branch is None else f" else {self.visit(ifelse.else_branch)}"
        return f"if {self.visit(ifelse.condition)} {self.visit(ifelse.if_branch)}{else_branch} endif"

    def visit_LBinary(self, lbinary: LBinary):
        return f"(L{lbinary.op} {self.visit(lbinary.left)} {self.visit(lbinary.right)})"

    def visit_Comparison(self, comparison: Comparison):
        return f"(Lc{comparison.op} {self.visit(comparison.left)} {self.visit(comparison.right)})"

    def visit_LLiteral(self, lliteral: LLiteral):
        return f"{lliteral.value}"

    def visit_LPrimary(self, lprimary: LPrimary):
        return f"#{self.visit(lprimary.primary)}"

    def visit_GetVector(self, getvector: GetVector):
        return f"{getvector.identifier.name}[{self.visit(getvector.vector_index)}]"

    def visit_Variable(self, variable: Variable):
        return f"{variable.identifier.name}"

    def visit_LNot(self, lnot: LNot):
        return f"!{self.visit(lnot.right)}"

    def visit_ABinary(self, abinary: ABinary):
        return f"(A{abinary.op} {self.visit(abinary.left)} {self.visit(abinary.right)})"

    def visit_AUMinus(self, auminus: AUMinus):
        return f"Au-{self.visit(auminus.right)}"

    def visit_ALiteral(self, aliteral: ALiteral):
        return f"{aliteral.value}"

    def visit_Call(self, call: Call):
        return f"{call.callee.name}({', '.join([self.visit(elem) for elem in call.arguments])})"

class PlaceType(Enum):
    String = 1
    Integer = 2
    Floating = 3
    Logical = 4
    # #
    StringVariable = 5
    IntegerVariable = 6
    FloatingVariable = 7
    LogicalVariable = 8
    EmptyVariable = 9
    # #
    Vector = 10

var_types = [PlaceType.LogicalVariable, 
            PlaceType.FloatingVariable, 
            PlaceType.IntegerVariable,
            PlaceType.StringVariable,
            PlaceType.EmptyVariable]

floats = [PlaceType.Floating, PlaceType.FloatingVariable]

ints = [PlaceType.Integer, PlaceType.IntegerVariable]

bools = [PlaceType.Logical, PlaceType.LogicalVariable]

strings = [PlaceType.String, PlaceType.StringVariable]

def find_type(literal, variable=False):
    if type(literal) == Place and literal.type in var_types:
        return literal.type
    elif type(literal) == Place:
        if literal.type == PlaceType.String:
            if variable:
                return PlaceType.StringVariable
            else:
                return PlaceType.String
        elif literal.type == PlaceType.Integer:
            if variable:
                return PlaceType.IntegerVariable
            else:
                return PlaceType.Integer
        elif literal.type == PlaceType.Floating:
            if variable:
                return PlaceType.FloatingVariable
            else:
                return PlaceType.Floating
        elif literal.type == PlaceType.Logical:
            if variable:
                return PlaceType.LogicalVariable
            else:
                return PlaceType.Logical
        elif literal.type == PlaceType.Param:
            # Only allowing integer values as function parameters
            return PlaceType.IntegerVariable
        else:
            print(f'Given literal {literal} does not correspond to any variable type')
            exit()
    else:
        print(f'What are you doing here? {literal}')

E = 0.00001

type_hierarchies = {PlaceType.Floating: 3, PlaceType.FloatingVariable: 3,
                    PlaceType.Integer: 2, PlaceType.IntegerVariable: 2,
                    PlaceType.Logical: 1, PlaceType.LogicalVariable: 1,
                    PlaceType.String: 0, PlaceType.StringVariable: 0}

hierarchy_to_type = {3: PlaceType.FloatingVariable,
                     2: PlaceType.IntegerVariable,
                     1: PlaceType.LogicalVariable,
                     0: PlaceType.StringVariable}

def cast_types(left, right):
    left_h = type_hierarchies[left.type]
    right_h = type_hierarchies[right.type]
    return hierarchy_to_type[max(left_h, right_h)]

class Place:
    def __init__(self, type : PlaceType, val):
        self.type = type
        self.val = val

    def __str__(self) -> str:
        return '{type:' + self.type.name + ', val: ' + str(self.val) + '}' 

    def __repr__(self) -> str:
        return self.__str__()

    def __eq__(self, other):
        # return self.type == other.type and self.val == other.val
        return self.val == other.val

    def __lt__(self, other):
        return self.val < other.val

    # Hashing will be used only for variables and vectors
    # which will only have strings as values
    # We also do not allow variables and vectors having the same name
    def __hash__(self) -> int:
        return hash(self.val)

class ILVisitor(ASTNodeVisitor):
    def __init__(self):
        super().__init__()
        self.il = []  # Will extend the already generated ils to this
        self.places = {'global': set()}
        self._tmp_count = 0
        self.strings = dict()
        self.params = dict()
        self.cur_scope = 'global'

    def _var_exists(self, var_name, scope, param=True):
        for place in self.places[scope]:
            if place.val == var_name:
                return place
        if param and scope != 'global':
            for param in self.params[scope]:
                if param.val == var_name:
                    return param
        return None

    def _extend_IL(self, il_instrs):
        self.il.extend(il_instrs)

    def _generate_tmp(self, var_type, scope):
        tmp = f'tmp{self._tmp_count}'
        self._tmp_count += 1
        place = Place(var_type, tmp)
        self.places[scope].add(place)
        return place

    def visit_SLiteral(self, sliteral: SLiteral):
        place = self._generate_tmp(PlaceType.String, self.cur_scope)
        self.strings[place] = repr(sliteral.value)
        return {'place': place, 'code': []}

    def visit_Program(self, program: Program):
        code = []
        for var_decl in program.var_decls:
            var_decls = self.visit(var_decl)
            code += var_decls['code']
        for fun_decl in program.fun_decls:
            fun_decls = self.visit(fun_decl)
            code += fun_decls['code']
        for statement in program.statements:
            stmts = self.visit(statement)
            code += stmts['code']
        return code

    def visit_ErrorStmt(self, errorstmt: ErrorStmt):
        print('Error statement encountered')
        exit()

    def visit_VarDecl(self, vardecl: VarDecl):
        # Does multiple declaration checking
        place_name = vardecl.identifier.name
        
        if self._var_exists(place_name, self.cur_scope, param=False):
            print(f'Error, variable {vardecl.identifier} is already declared in {self.cur_scope}')
            exit()
        
        if vardecl.initializer is not None and type(vardecl.initializer) == list:
            # TODO: This is a vector initialization, implement it
            # last_expr = None
            # for stmt in vardecl.initializer:
            #     print(stmt)
            #     last_expr = self.visit(stmt)
            pass
        elif vardecl.initializer is not None:
            expr = self.visit(vardecl.initializer)
            place = Place(find_type(expr['place'], variable=True), place_name)
            self.places[self.cur_scope].add(place)
            code = expr['code'] + [('COPY', place, expr['place'])]
        else:
            place = Place(PlaceType.EmptyVariable, place_name)
            code = []
            self.places[self.cur_scope].add(place)
        return {'place': place, 'code': code}

    def visit_FunDecl(self, fundecl: FunDecl):
        id = fundecl.identifier.name
        params = []
        for param in fundecl.params:
            # It assumes that every parameter is an integer, this includes logical values as well
            # 1 for true, 0 for false
            params.append(Place(PlaceType.IntegerVariable, param.name))

        self.params[id] = params
        self.cur_scope = id
        self.places[id] = set()
        body = self.visit(fundecl.body)
        code = [('FUN', id, body)]
        self.cur_scope = 'global'
        return {'code': code}

    def visit_Assign(self, assign: Assign):
        place_name = assign.identifier.name
        var = self._var_exists(place_name, self.cur_scope)
        if not var:
            print(f'Error, variable {assign.identifier} is assigned before declaration in {self.cur_scope}')
            exit()

        expr = self.visit(assign.expr)
        self.places[self.cur_scope].remove(var)
        var = Place(find_type(expr['place'], variable=True), place_name)
        self.places[self.cur_scope].add(var)
        code = expr['code'] + [('COPY', var, expr['place'])]
        return {'place': var, 'code': code}

    def visit_SetVector(self, setvector: SetVector):
        pass
        # return f"{setvector.identifier.name}[{self.visit(setvector.vector_index)}] = {self.visit(setvector.expr)};"

    def visit_ForLoop(self, forloop: ForLoop):
        pass
        # initializer = '' if forloop.initializer is None else self.visit(forloop.initializer)[:-1]
        # condition = '' if forloop.condition is None else self.visit(forloop.condition)
        # increment = '' if forloop.increment is None else self.visit(forloop.increment)[:-1]
        # return f"for ({initializer};{condition};{increment}) {self.visit(forloop.body)}"

    def visit_Return(self, returnn: Return):
        expr = self.visit(returnn.expr)
        code = [('RETURN', expr)]
        return {'code': code}

    def visit_WhileLoop(self, whileloop: WhileLoop):
        cond = self.visit(whileloop.condition)
        body = self.visit(whileloop.body)
        code = [('WHILE', cond, body)]
        return {'code': code}

    def visit_Block(self, block: Block):
        var_decls = []
        for var_decl in block.var_decls:
            var_decls.append(self.visit(var_decl)['code'])
        
        stmts = []
        for stmt in block.statements:
            stmts.append(self.visit(stmt)['code'])

        code = [('BLOCK', var_decls, stmts)]
        return {'code': code}

    def visit_Print(self, printt: Print):
        pass
        # return f"print {self.visit(printt.expr)};"

    def visit_IfElse(self, ifelse: IfElse):
        cond = self.visit(ifelse.condition)
        if_part = self.visit(ifelse.if_branch)
        if ifelse.else_branch:
            else_part = self.visit(ifelse.else_branch)
        else:
            else_part = {'code': []}
        code = [('IFELSE', cond, if_part, else_part)]
        return {'code': code}

    def visit_LBinary(self, lbinary: LBinary):
        left = self.visit(lbinary.left)
        right = self.visit(lbinary.right)
        place = self._generate_tmp(PlaceType.LogicalVariable, self.cur_scope)
        code = left['code'] + right['code'] + [(lbinary.op.upper(), place, left['place'], right['place'])]
        return {'place': place, 'code': code}

    def visit_Comparison(self, comparison: Comparison):
        left = self.visit(comparison.left)
        right = self.visit(comparison.right)
        place = self._generate_tmp(PlaceType.LogicalVariable, self.cur_scope)
        code = left['code'] + right['code'] + [(comparison.op, place, left['place'], right['place'])]
        return {'place': place, 'code': code}

    def visit_LLiteral(self, lliteral: LLiteral):
        return {'place': Place(PlaceType.Logical, lliteral.value), 'code': []}

    def visit_LPrimary(self, lprimary: LPrimary):
        # TODO: Implement this once you get a response from Cem Hoca
        # Union[Call, GetVector, Variable]
        if type(lprimary.primary) == Call:
            # TODO: Implement this with function calls
            pass
        elif type(lprimary.primary) == GetVector:
            # TODO: Implement this with vectors
            pass
        else:
            # Is of type variable
            res = self.visit(lprimary.primary)
            # TODO: Add types to places and check for equality to 0 depending on the type
            pass
        # return f"#{self.visit(lprimary.primary)}"

    def visit_GetVector(self, getvector: GetVector):
        pass
        # return f"{getvector.identifier.name}[{self.visit(getvector.vector_index)}]"

    def visit_Variable(self, variable: Variable):
        place_name = variable.identifier.name
        var = self._var_exists(place_name, self.cur_scope)
        if not var:
            print(f'Error, variable {variable.identifier} used before declaration')
            exit()
        return {'place': var, 'code': []}

    def visit_LNot(self, lnot: LNot):
        right = self.visit(lnot.right)
        place = self._generate_tmp(PlaceType.LogicalVariable, self.cur_scope)
        code = right['code'] + [('NOT', place, right['place'])]
        return {'place': place, 'code': code}

    def visit_ABinary(self, abinary: ABinary):
        left = self.visit(abinary.left)
        right = self.visit(abinary.right)
        if left['place'].type in strings or right['place'].type in strings:
            print(f'Left or right operand is a string, which is not supported for arithmetic ops. {left}, {right}')
            exit()
        casted_type = cast_types(left['place'], right['place'])
        place = self._generate_tmp(casted_type, self.cur_scope)
        code = left['code'] + right['code'] + [(abinary.op, place, left['place'], right['place'])]
        return {'place': place, 'code': code}

    def visit_AUMinus(self, auminus: AUMinus):
        right = self.visit(auminus.right)
        place = self._generate_tmp(find_type(right['place'], variable=True), self.cur_scope)
        code = right['code'] + [('UMINUS', place, right['place'])]
        return {'place': place, 'code': code}

    def visit_ALiteral(self, aliteral: ALiteral):
        if abs(int(aliteral.value) - aliteral.value) < E:
            type_of_literal = PlaceType.Integer
        else:
            type_of_literal = PlaceType.Floating
        return {'place': Place(type_of_literal, aliteral.value), 'code': []}

    def visit_Call(self, call: Call):
        callee = call.callee
        args = call.arguments

        place = self._generate_tmp(PlaceType.IntegerVariable, self.cur_scope)

        id = callee.name
        if id not in self.places:
            print(f'Function {id} is not declared before')
            exit()

        arg_code = []
        for arg in args:
            arg_code.append(self.visit(arg))

        code = [('CALL', place, arg_code, id)]

        return {'place': place, 'code': code}