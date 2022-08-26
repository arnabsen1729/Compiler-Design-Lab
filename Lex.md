# Lex & Yacc

Yacc is used for Syntax analyzer or parser.
Lex is used for Lexical analysis.

## Lex working

Lex reads patterns from the `*.l` file and generates a lexical analyzer function `yylex` in the file `lex.yy.c`.

## Lex Theory

Lex consists of **patterns** and corresponding **actions**. In most cases the action returns a token.

Regular Expression expressions can be expressed as a finite state automaton (FSA).

## Primitives

| Metacharacter | Matches |
|---|---|
| $\cdot$ | any character except newline |
| `\n` | newline |
| `*` | zero or more copies |
| `+` | one or more copies | 
| `?` | zero or one |
| `^` | beginning of the line |
| `$` | end of the line |
| `a|b` | a or b |
| `(ab)+` | one or more copies of ab |
| `"a+b"` | literal "a+b" |
| `[]` | character class |

> NOTE: `^` inside character class represents negation of the set, e.g `[^ab]` represents anything except a, b.

If two patterns match the same string the longest match wins. If both match are of same length then the first pattern listed is used.

## Lex Structure

```c
...definitions...
%%
...rules...
%%
...subroutines...
```

In the rules, we follow:

```
<pattern> <action (optional)>
```

The action maybe a single C statement or multiple C statements enclosed in braces.

Variables:

**yylex** main entry-point for lex.
**yytext** pointer to the matched string (NULL terminated).
**yyleng** length of the matched string.
**yyout** output file (default: stdout).
**yywrap** called by lex when the input is exhausted. (return 1 if done, 0 otherwise)





