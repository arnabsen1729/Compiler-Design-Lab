# Lexical Analysis

## Lexical Analyzer

The main purpose of a lexical analyzer is to translate input stream into a form that is manageable by the parser.

**Lexeme** is a sequence of characters representing a syntactical unit of a language. For example: "123", "while", "for".

**Token** is a pair consisting of a token name and an optional attribute value. It is an abstract symbol representing a kind of lexical unit, i.e a particular keyword or a sequence of input characters denoting an identifier. For example: "123" lexeme is of token INTCONST, "while" lexeme is of token WHILE_TOK etc.

## Lexical Errors

- When a sequence of characters doesn't match the pattern of any token.
- When it comes across some kind of illegal character like, $ outside a string in C.

## Concepts

- **Alphabet** is a finite set of symbols, e.g {'0', '1'} is a binary alphabet. 
- **String** or **Word** is a sequence of alphabetic symbols, e.g "0101" is a binary string.
- 

