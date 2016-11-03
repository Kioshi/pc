CC = gcc
CFLAGS = -Wall -pedantic -ansi -Wno-unknown-pragmas
LDFLAGS = -lm
BIN = fssim.exe
OBJ = main.o node.o string.o array.o fssim.o util.o

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN): $(OBJ)
		$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm $(OBJ)

