MATRIX_OBJ_DEPS=convolution.c new.c matrix.c
MATRIX_OBJS=$(foreach dep, $(MATRIX_OBJ_DEPS), $(BIN)/$(dep).o)

$(MATRIX_OBJ_DEPS): %:
	$(CC) $(CFLAGS) -c $(MATRIX_DIR)/$@ -o $(BIN)/$@.o
