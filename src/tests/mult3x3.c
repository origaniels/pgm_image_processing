#include "matrix.h"
#include <assert.h>
#include <stdio.h>

uint16_t main() {
  uint16_t n = 3;
  uint16_t m = 3;
  uint16_t weights[9] = {
                          1, 2, 3,
                          3, 1, 2,
                          2, 3, 1
                        };
  struct matrix *a = matrix_from(n, m, weights);

  uint16_t weights2[9] = {
                          1, 2, 4,
                          8, 16, 32,
                          64, 128, 255,
                        };
  struct matrix *b = matrix_from(n, m, weights2);

  struct matrix *c = matrix_new(n, m);
  matmult3x3(a, b, c);

  uint16_t exp_weights[9] = {
                            209, 418, 833,
                            139, 278, 554,
                            90, 180, 359
                            };
  struct matrix *expect = matrix_from(n, m, exp_weights);

  if (matrix_equals(expect, c))
    printf("Success\n");
}
