## A Compiler for the Vox Language
#### Aral Yekta Yarımca - 2376093

The compiler can be used as
```
    python3 vox.py example.vox
```

Where example.vox is a file containing the source code of a Vox program. 
Providing source code paths as relative addresses is supported.

What can this compiler do?

- It can generate the RISCV assembly code of the given source code
- It supports simple arithmetic instructions, like + - / *
- It supports short circuiting and/or operations
- It supports variable declarations and assignments
- It checks variable usage before declaration, or multiple declarations in the same block
- It allows function declarations and invocations. Also uses shadowing and parameter passing while doing so. However, parameter passing is only implemented for the addition and the assignment (including variable declaration) operations due to the limited time. However, its implementation for the remaining operations are pretty much similar to that of addition and copying. 
- It allows for value comparison. However, only the < operation is currently supported. But its implementation for !=, ==, >, <= and >= is pretty similar to that of <, as explained in the relevant comment section.
- It supports unary minus operations.
- It does NOT support strings yet. It can only declare them in the data field.
- If-else and while are implemented.
- It supports real numbers only for arithmetics and in the condition that there is no parameter passing

For more info, you can check the source code comments. Especially in the file called "asmgen.py".