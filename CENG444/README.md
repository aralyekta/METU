# CENG444

In the course, I wrote a compiler for a C-like language called Vox. Vox is a modified version of Lox, which can be found here: https://craftinginterpreters.com/the-lox-language.html. Also, the specs of the modified version (Vox) is present in this folder as "vox_specs.txt".

## Project 1 (Lexer)

This project reads a source code and separates it into tokens. The project can be run with

>python3 main.py

## Project 2 (Lexer + Parser + RISCV Generator)

This project reads a source code, separates it into tokens, creates an abstract syntax tree out of it, and finally generates the appropriate RISCV assembly code of it, resulting in an assembly file (.asm) that could be run with a RISCV emulator.
The project can be run with

>python3 parser/main.py

Even though this stage of the project is not complete, it supports most of the functionalities of a programming language such as function calls (with stack preparations), variable accesses and modifications, type coercions etc.
