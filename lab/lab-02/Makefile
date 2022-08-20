CXX = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = lexer
OBJFILES = lexer.o

all: ${TARGET}

${TARGET}: ${OBJFILES}
	${CXX} ${OBJFILES} -o ${TARGET}

lexer.o: lexer.c
	${CXX} ${CFLAGS} -O -c lexer.c

clean:
	rm -f ${TARGET} ${OBJFILES}