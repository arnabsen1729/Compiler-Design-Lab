all: lexer

lexer: lexer.l
	lex lexer.l
	gcc lex.yy.c -ll -o lexer

clean:
	rm -f lex.yy.c lexer