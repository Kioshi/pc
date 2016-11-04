CC = gcc
CFLAGS = -Wall -pedantic -ansi -Wno-unknown-pragmas
LDFLAGS = -lm
BIN = fssim.exe
OBJ = main.o node.o string.o array.o fssim.o util.o
DOC=doc
RM=rm -Rf
SRCDIR=src

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

#Documentation
doc:
	doxygen Doxyfile

clean:
	$(RM) $(OBJ) $(DOC) $(BIN)
