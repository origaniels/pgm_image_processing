#include "matrix.h"
#include <stdio.h>
#include <assert.h>

int main() {
  uint16_t n = 3;
  uint16_t m = 3;
  int32_t weights[9] = {
                          1, 2, 3,
                          4, 5, 6,
                          7, 8, 9
                        };
  struct matrix *a = matrix_from(n, m, weights);

  int32_t weights2[9] = {
                          1, 1, 1,
                          1, 1, 1,
                          1, 1, 1
                        };
  struct matrix *b = matrix_from(n, m, weights2);

  struct matrix * c = convolve2d(a, b);
  int32_t expect[9] = {
                          21, 27, 33,
                          39, 45, 51,
                          57, 63, 69
                      };
  struct matrix *expect_mat = matrix_from(n, m, expect);


  assert(matrix_equals(c, expect_mat));
}
