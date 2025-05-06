

print: 	matrix
	$(CC) $(CFLAGS) $(TEST_DIR)/prettyprint.c $(BIN)/matrix.o -o $(BIN)/prettyprint

open: 	pgm
	$(CC) $(CFLAGS) $(TEST_DIR)/openimage.c $(BIN)/matrix.o $(BIN)/pgm.o -o $(BIN)/openimage

close: 	pgm
	$(CC) $(CFLAGS) $(TEST_DIR)/copy_image.c $(BIN)/matrix.o $(BIN)/pgm.o -o $(BIN)/copy_image

mult33: matrix
	$(CC) $(CFLAGS) $(TEST_DIR)/mult3x3.c $(BIN)/matrix.o -o $(BIN)/mult33

equals: matrix
	$(CC) $(CFLAGS) $(TEST_DIR)/equals.c $(BIN)/matrix.o -o $(BIN)/equals

pad: matrix
	$(CC) $(CFLAGS) $(TEST_DIR)/padding.c $(BIN)/matrix.o -o $(BIN)/padding

extract: matrix
	$(CC) $(CFLAGS) $(TEST_DIR)/extract_matrix_block.c $(BIN)/matrix.o -o $(BIN)/extract_matrix_block

convolve: matrix
	$(CC) $(CFLAGS) $(TEST_DIR)/convolve.c $(BIN)/matrix.o -o $(BIN)/convolve

convolve2d: matrix
	$(CC) $(CFLAGS) $(TEST_DIR)/convolve2d.c $(BIN)/matrix.o -o $(BIN)/convolve2d

