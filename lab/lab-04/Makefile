all:
	yacc -d parser.y 
	lex lexer.l
	gcc y.tab.c -ll -o lexer

run:
	./lexer < source.c

clean:
	rm -f lex.yy.c lexer y.tab.c y.tab.h