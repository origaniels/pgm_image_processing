#include "include/pgm.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int32_t *double_block(int32_t *src, int size) {
  int32_t *res = malloc(size * size * 4 * sizeof(int32_t));
  for (int i = 0; i<2 * size; i++) {
    for (int j = 0; j<2 * size; j++) {
      int src_i = i>=size ? i-size : i;
      int src_j = j>=size ? j-size : j;
      res[i * 2 * size + j] = src[src_i * size + src_j];
    }
  }
  return res;
}

int32_t *increment_size(int32_t *src, int size, int total_size) {
  int32_t *res = malloc(total_size * total_size * sizeof(int32_t));
  for (int i = 0; i<total_size; i++) {
    for (int j = 0; j<total_size; j++) {
      int src_i = i%size;
      int src_j = j%size;
      res[i * total_size + j] = src[src_i * size + src_j];
    }
  }
  return res;
}


void save(struct matrix *m, char *name) {
  struct pgm *image = matrix_to_pgm(m, 255);
  pgm_to_image(image, name);
}

int main() {
  uint16_t n = 3;
  uint16_t m = 3;
  int32_t weights[1024] = {
                          0, 0,   0,    0,   0,   0,    0,    0,   0,   0,   0,    0,   0,   0,    0,    0,   0,   0,   0,    0,   0,   0,    0,    0,   0,   0,   0,    0,   0,    0,    0, 0,
                          0, 0,   0,    0,   0,   0,    0,    0,   0,   0,   0,    0,   0,   0,    0,    0,   0,   0,   0,    0,   0,   0,    0,    0,   0,   0,   0,    0,   0,    0,    0, 0,
                          0, 0,   0,    0, 255, 255,  255,  255, 255, 255, 255,  255, 255, 255,  255,  255, 255, 255, 255,  255, 255, 255,  255,  255, 255, 255, 255,  255,   0,    0,    0, 0,
                          0, 0,   0,    0, 255, 255,  255,  255, 255, 255, 255,  255, 255, 255,  255,  255, 255, 255, 255,  255, 255, 255,  255,  255, 255, 255, 255,  255,   0,    0,    0, 0,
                          0, 0,   0,    0, 255, 255,  255,  255, 255, 255, 255,  255, 255, 255,  255,  255, 255, 255, 255,  255, 255, 255,  255,  255, 255, 255, 255,  255,   0,    0,    0, 0,
                          0, 0,   0,    0, 255, 255,  255,  255, 255, 255, 255,  255, 255, 255,  255,  255, 255, 255, 255,  255, 255, 255,  255,  255, 255, 255, 255,  255,   0,    0,    0, 0,
                          0, 0,   0,    0, 255, 255,  255,  255, 255, 255, 255,  255, 255, 255,  255,  255, 255, 255, 255,  255, 255, 255,  255,  255, 255, 255, 255,  255,   0,    0,    0, 0,
                          0, 0,   0,    0, 255, 255,  255,  255, 255, 255, 255,  255, 255, 255,  255,  255, 255, 255, 255,  255, 255, 255,  255,  255, 255, 255, 255,  255,   0,    0,    0, 0,
                          0, 0,   0,    0, 255, 255,  255,  255, 255, 255, 255,  255, 255, 255,  255,  255, 255, 255, 255,  255, 255, 255,  255,  255, 255, 255, 255,  255,   0,    0,    0, 0,
                          0, 0,   0,    0, 255, 255,  255,  255, 255, 255, 255,  255, 255, 255,  255,  255, 255, 255, 255,  255, 255, 255,  255,  255, 255, 255, 255,  255,   0,    0,    0, 0,
                          0, 0,   0,    0,   0,   0,    0,    0,   0,   0,   0,    0,   0,   0,    0,    0,   0,   0,   0,    0,   0,   0,    0,    0,   0,   0,   0,    0,   0,    0,    0, 0,
                          0, 0,   0,    0,   0,   0,    0,    0,   0,   0,   0,    0,   0,   0,    0,    0,   0,   0,   0,    0,   0,   0,    0,    0,   0,   0,   0,    0,   0,    0,    0, 0,
                        };
  struct matrix *cur;
  int32_t *w = weights;
  int matrix_size = 32;
  for (int i = 0; i<200; i++) {
    w = increment_size(weights, 32, matrix_size);
    cur = matrix_from(matrix_size, matrix_size, w);
    if (i==0) {
      matrix_prettyprint(cur);
    }
    char filename[20];
    sprintf(filename, "rects/rect%dx%d", matrix_size, matrix_size);
    save(cur, filename);
    matrix_size += 32;
  }
}
