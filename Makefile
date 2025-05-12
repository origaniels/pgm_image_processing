CFLAGS=-Isrc -O3 -pg -g3 -fsanitize=signed-integer-overflow 
LDFLAGS=-lm
BIN=bin
CC?=gcc

SOURCE_DIR=src
MATRIX_DIR=$(SOURCE_DIR)/matrix
PGM_DIR=$(SOURCE_DIR)/pgm
TEST_DIR=$(SOURCE_DIR)/tests

all: 	edge

# libs
include $(MATRIX_DIR)/matrix.mk
include $(PGM_DIR)/pgm.mk

# tests
include $(TEST_DIR)/tests.mk

# frontends
blur: 	$(MATRIX_OBJ_DEPS) pgm
	$(CC) $(CFLAGS) src/blur.c $(BIN)/matrix.o $(BIN)/pgm.o

edge: 	$(MATRIX_OBJ_DEPS) pgm
	$(CC) $(CFLAGS) src/edge_detect.c $(MATRIX_OBJS) $(BIN)/pgm.o $(LDFLAGS) -o $(BIN)/edge_detect

big: 	$(MATRIX_OBJ_DEPS) pgm
	$(CC) $(CFLAGS) src/big_generator.c $(MATRIX_OBJS) $(BIN)/pgm.o $(LDFLAGS) -o $(BIN)/big_generator


