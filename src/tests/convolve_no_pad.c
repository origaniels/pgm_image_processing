#include "matrix/matrix_internals.h"
#include <stdio.h>

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
                          1, 0, 3,
                          0, 0, 0,
                          2, 0, 4
                        };
  struct matrix *b = matrix_from(n, m, weights2);

  int32_t c = convolve_without_padding(a, b, 2, 2);
  printf("%d\n", c);
}
