CFLAGS=-Isrc -O0 -g3 -fsanitize=signed-integer-overflow -lm 
BIN=bin

all: 	edge

# libs
matrix:
	gcc $(CFLAGS) -c src/matrix.c -o $(BIN)/matrix.o

pgm: 	matrix
	gcc $(CFLAGS) -c src/pgm.c -o $(BIN)/pgm.o


# tests
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

pad: matrix
	gcc $(CFLAGS) src/tests/padding.c $(BIN)/matrix.o -o $(BIN)/padding

extract: matrix
	gcc $(CFLAGS) src/tests/extract_matrix_block.c $(BIN)/matrix.o -o $(BIN)/extract_matrix_block

convolve: matrix
	gcc $(CFLAGS) src/tests/convolve.c $(BIN)/matrix.o -o $(BIN)/convolve

convolve2d: matrix
	gcc $(CFLAGS) src/tests/convolve2d.c $(BIN)/matrix.o -o $(BIN)/convolve2d

blur: 	matrix pgm
	gcc $(CFLAGS) src/blur.c $(BIN)/matrix.o $(BIN)/pgm.o

edge: 	matrix pgm
	gcc $(CFLAGS) src/edge_detect.c $(BIN)/matrix.o $(BIN)/pgm.o -o $(BIN)/edge_detect

