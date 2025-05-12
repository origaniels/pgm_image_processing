

print: 	$(MATRIX_OBJ_DEPS)
	$(CC) $(CFLAGS) $(TEST_DIR)/prettyprint.c $(MATRIX_OBJS) $(LDFLAGS) -o $(BIN)/prettyprint

open: 	pgm
	$(CC) $(CFLAGS) $(TEST_DIR)/openimage.c $(MATRIX_OBJS) $(BIN)/pgm.o $(LDFLAGS) -o $(BIN)/openimage

close: 	pgm
	$(CC) $(CFLAGS) $(TEST_DIR)/copy_image.c $(MATRIX_OBJS) $(BIN)/pgm.o $(LDFLAGS) -o $(BIN)/copy_image

mult33: $(MATRIX_OBJ_DEPS)
	$(CC) $(CFLAGS) $(TEST_DIR)/mult3x3.c $(MATRIX_OBJS) $(LDFLAGS) -o $(BIN)/mult33

equals: $(MATRIX_OBJ_DEPS)
	$(CC) $(CFLAGS) $(TEST_DIR)/equals.c $(MATRIX_OBJS) $(LDFLAGS) -o $(BIN)/equals

pad: $(MATRIX_OBJ_DEPS)
	$(CC) $(CFLAGS) $(TEST_DIR)/padding.c $(MATRIX_OBJS) $(LDFLAGS) -o $(BIN)/padding

extract: $(MATRIX_OBJ_DEPS)
	$(CC) $(CFLAGS) $(TEST_DIR)/extract_matrix_block.c $(MATRIX_OBJS) $(LDFLAGS) -o $(BIN)/extract_matrix_block

convolve: $(MATRIX_OBJ_DEPS)
	$(CC) $(CFLAGS) $(TEST_DIR)/convolve.c $(MATRIX_OBJS) $(LDFLAGS) -o $(BIN)/convolve

convolve_no_pad: $(MATRIX_OBJ_DEPS)
	$(CC) $(CFLAGS) $(TEST_DIR)/convolve_no_pad.c $(MATRIX_OBJS) $(LDFLAGS) -o $(BIN)/convolve_no_pad

convolve2d: $(MATRIX_OBJ_DEPS)
	$(CC) $(CFLAGS) $(TEST_DIR)/convolve2d.c $(MATRIX_OBJS) $(LDFLAGS) -o $(BIN)/convolve2d

