PGM_OBJ_DEPS=


$(PGM_OBJ_DEPS): %: %.c
	$(CC) $(CFLAGS) -o $@ $<

pgm: $(PGM_OBJ_DEPS)
	$(CC) $(CFLAGS) -c $(PGM_DIR)/pgm.c $(PGM_OBJ_DEPS) -o $(BIN)/pgm.o

