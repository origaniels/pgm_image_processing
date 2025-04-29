CFLAGS="-Isrc"
BIN="bin"

matrix:
	gcc $(CFLAGS) -c src/matrix.c -o $(BIN)/matrix.o

print: matrix
	gcc $(CFLAGS) src/tests/prettyprint.c $(BIN)/matrix.o -o $(BIN)/prettyprint

all: matrix
	gcc $(CFLAGS) src/main.c $(BIN)/matrix.o

