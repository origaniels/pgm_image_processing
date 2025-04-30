#include "matrix.h"

int main() {
  uint16_t n = 4;
  uint16_t m = 4;
  uint16_t weights[16] = {
                          1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1
                        };
  struct matrix *a = matrix_from(n, m, weights);
  matrix_prettyprint(a);

  uint16_t weights2[16] = {
                          1, 0, 0, 4,
                          0, 1, 6, 0,
                          0, 8, 1, 0,
                          2, 0, 0, 1
                        };
  a = matrix_from(n, m, weights2);
  matrix_prettyprint(a);
}
