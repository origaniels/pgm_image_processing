CFLAGS=-Isrc
BIN=bin

matrix:
	gcc $(CFLAGS) -c src/matrix.c -o $(BIN)/matrix.o

print: matrix
	gcc $(CFLAGS) src/tests/prettyprint.c $(BIN)/matrix.o -o $(BIN)/prettyprint

mult33: matrix
	gcc $(CFLAGS) src/tests/mult3x3.c $(BIN)/matrix.o -o $(BIN)/mult33

equals: matrix
	gcc $(CFLAGS) src/tests/equals.c $(BIN)/matrix.o -o $(BIN)/equals

all: matrix
	gcc $(CFLAGS) src/main.c $(BIN)/matrix.o

