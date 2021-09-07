# Brainfuck C Compiler

Make this program use it to compile a program.
```bash
$ cd ccompiler
$ make
$ ./bfcc [NAME_OF_FILE]
```

This creates an intermediary C file called `b.c`. And this C file is compiled into a binary file (`a.out`) using GCC.

There are some brainfuck programs available in `../testing`.
```bash
$ ./bfcc ../testing/mandelbrot.bf
$ ./a.out
```
