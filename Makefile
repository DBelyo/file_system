CC=gcc
CFLAGS=-Wall
DEPS=lib/arbre.h lib/liste.h lib/instruction.h lib/debug.h lib/exit.h
EXEC=treedir

all : build
	./$(EXEC) tests/base.txt --debug

build : ${EXEC}

clean :
	rm -rf $(EXEC) *.o main treedir log

%.o: lib/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

treedir : treedir.o arbre.o liste.o instruction.o debug.o exit.o
	$(CC) $(CFLAGS) -o $@ $^
