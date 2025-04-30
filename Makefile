CFLAGS=-Isrc -g
BIN=bin

matrix:
	gcc $(CFLAGS) -c src/matrix.c -o $(BIN)/matrix.o

pgm: 	matrix
	gcc $(CFLAGS) -c src/pgm.c -o $(BIN)/pgm.o

print: 	matrix
	gcc $(CFLAGS) src/tests/prettyprint.c $(BIN)/matrix.o -o $(BIN)/prettyprint

open: 	pgm
	gcc $(CFLAGS) src/tests/openimage.c $(BIN)/matrix.o $(BIN)/pgm.o -o $(BIN)/openimage

close: 	pgm
	gcc $(CFLAGS) src/tests/copy_image.c $(BIN)/matrix.o $(BIN)/pgm.o -o $(BIN)/copy_image

mult33: matrix
	gcc $(CFLAGS) src/tests/mult3x3.c $(BIN)/matrix.o -o $(BIN)/mult33

equals: matrix
	gcc $(CFLAGS) src/tests/equals.c $(BIN)/matrix.o -o $(BIN)/equals

all: 	matrix
	gcc $(CFLAGS) src/main.c $(BIN)/matrix.o

