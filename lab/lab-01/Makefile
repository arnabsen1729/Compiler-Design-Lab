CXX = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = lexer
OBJFILES = lexer.o utils.o

all: ${TARGET}

${TARGET}: ${OBJFILES}
	${CXX} ${OBJFILES} -o ${TARGET}

lexer.o: lexemes.h lexer.c
	${CXX} ${CFLAGS} -O -c lexer.c

utils.o: utils.h utils.c
	${CXX} ${CFLAGS} -O -c utils.c

clean:
	rm -f ${TARGET} ${OBJFILES}
