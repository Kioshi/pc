CC = gcc
CFLAGS = -g -Wall -pedantic -ansi -Wno-unknown-pragmas
LDFLAGS = -lm
BIN = fssim.exe
OBJ = main.o node.o string.o array.o fssim.o util.o
DOC=doc
RM=rm -Rf
SRCDIR=.

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

#Documentation
doc:
	doxygen Doxyfile
   
#Clean all created files
clean:
	$(RM) $(OBJ) $(DOC) $(BIN)
                                    
#Number of lines (including comments)
count:
	wc -l $(SRCDIR)/*.h $(SRCDIR)/*.c
