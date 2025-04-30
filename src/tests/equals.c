#include "matrix.h"
#include <assert.h>
#include <stdio.h>

int main() {
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

  
  if (!matrix_equals(a, b))
    if (matrix_equals(a, a))
      printf("Success\n");
}
