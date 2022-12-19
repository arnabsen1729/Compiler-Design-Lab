# Compiler Design

## Books

### Theory

- [Ullman's Compiler Design](https://www-2.dc.uba.ar/staff/becher/dragon.pdf)
- [Compiler Design in C by Holub](./books/Compiler_Design_In_C_Holub.pdf)
- [Basics of Compiler Design](./books/Basics_Of_Compiler_Design.pdf)

### Lex and Yacc

- [Lex and Yacc](./books/Lex_and_Yacc_Tutorial.pdf)
- [Compact guide to Lex and Yacc](./books/CompactGuideToLexYacc.pdf)

## Slides

- [01 Introduction to Compiler Design](./slides/01_Intro_Compiler_Design.pdf)
- [02 Lex Part-1](./slides/02_Lex_Compiler_Design.pdf)
- [03 Lex Part-2](./slides/03_Lex_Compiler_Design.pdf)
- [04 Syntax Analyser](./slides/04_Syntax-Analyser.pdf)
- [05 Symbol Table](./slides/05_Symbol_Table.pdf)
- [06 Error Recovery](./slides/06_Error_Recovery.pdf)
- [07 Semantic Analysis](./slides/07_Semantic_Analysis.pdf)
- [08 Intermediate Code](./slides/08_Intermediate_Code.pdf)
- [09 RunTime Environment](./slides/09_RunTime_Env.pdf)
- [10 Code Generation](./slides/10_Code_Gen.pdf)

## Viva Notes

- [Compiler Design Viva Notes](./lab/compiler-design-viva.pdf)

## Lab Work

To run the lab work, you need to install `flex` (for LeX) and `bison` (for Yacc).

```bash
sudo apt-get install flex
sudo apt-get install bison
```

To compile the code use the `make` tool. To install `make` use the following command.

```bash
sudo apt-get -y install make
```

Once `make` is installed

- Go to the lab directory
- Run `make` command to generate the lex and yacc files and compile the binary
- Run `make run` to execute the binary with the input file
- Run `make clean` to remove the generated files before submitting

```bash
cd lab/lab-04
make
make run
make clean
```

## YouTube

- [Compiler Design Playlist by Gate Smasher](https://www.youtube.com/playlist?list=PLxCzCOWd7aiEKtKSIHYusizkESC42diyc)