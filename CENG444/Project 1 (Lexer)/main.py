from lexer import Lexer
from parser_1 import Parser
from misc import process, generate_ast

if __name__ == '__main__':
    data1 = '''whileee while he!+-*/34234.234=="fun"fun funnn ifelse if else ===>=>>=<=<== "test'''
    data2 = '''.435435 = == funwhile whileee fun(){}n"fun" "[" []];;; "var else" if nil'''
    data3 = '''.43534543.435345345'''
    data4 = '''test.nofieldsinvox //whoa a comment else if if else
    while fun //another one 1231242
    //.123123
    1231.312312 .12313. //"test"'''
    data5 = '''eand or orand andor ==or else iffun fun ""else"" test.123.21332 test 123notvarname truefalse true // false "false"
    false "true" "falsee" falsee falsetrue truee'''
    data6 = '''x[2]'''
    data7 = '''x'''
    data8 = '''"asdasd"'''
    data9 = '''false'''
    data10 = '''true'''
    data11 = '''if'''
    data12 = '''ifa'''
    data13 = '''truefalse true // false "false"
    false "true" "falsee" falsee falsetrue truee'''
    data14 = '''func()'''
    data15 = '''func(a)'''
    data16 = '''func(a, b, c)'''
    data16 = '''a, b, c'''
    data17 = '''var a;
    var b;'''
    parser_test1 = '''var a;
var b;
var y;
var b;
fun f(a, b, d){
var c;
var d;
e = #d;
if x == 3 {
var d;
var e = f();
var f = d;
var c;
e = y+3;
}
}
a = --a+3*5-4+f;
e = 345;
while(a == 3){
    x = 5;
    if true{
    var x;
    var z;
    var x;
    }}
'''
    parser_test2 = '''var a;
var b;
var z = 100;
fun f(f,f,f){
  var f;
  var x = 0;
  var z = 0;
  for(x=0;x < 10;x = x+1){
    var z; //scopes are cool!
    y = y+1;
    while y > 0 {
      var q = [2,4,6,true,false,#f(),undeclared];
      y = y-1;
      z = z+x;
        if true q = y-1;
    }
  }
}
 '''
    parser_test3 = '''var a;
var c; // parse error again
while(a == 3){
  var b; //scopes to declare more variables
  var c;
  var b;
  print #b;
  print b;
  return c; //semantically incorrect but we don't check it for this assignment
  x = #y or #l and #x() or 3*-6+5-3----3+8*4/2+7 < 5*f(a(4+5,7,88,x),4);
}'''
    parser_test4 = '''//a program full of semantic errors (that we don't check in this assignment)
var a;

var b = [3, 5];

var c = [true, false, b];
fun a(){}
fun b(a,b){
  var c = a((#a));
  while(#a[b+3]){}
  if true if true if true {var c; a = 3; b= 5;} else a = 5; else a =6;
  return b;
}
a = "hello";
a = a[a[a[a+2]]]+3;'''
    parser_test5 = '''var important_advice = "Start writing your parser early!!! :)";
fun fibonacci(n){
  if n <= 1 return 1;
  else return fibonacci(n-1)+fibonacci(n-2);
}
print important_advice;
print fibonacci(10);
'''

    # lexer = Lexer()
    # parser = Parser()
    # tokens = lexer.tokenize(case7)
    # # for token in tokens:
    # #     print(token)
    # res = parser.parse(tokens)
    # print(res)

    result = process(parser_test1)
    ast = generate_ast(result)
