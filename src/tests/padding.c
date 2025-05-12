#include "matrix/matrix_internals.h"
#include <assert.h>
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

  int32_t expect[63] = {
      1, 1,  1, 2, 3,  3, 3,
      1, 1,  1, 2, 3,  3, 3,
      1, 1,  1, 2, 3,  3, 3,

      1, 1,  1, 2, 3,  3, 3,
      4, 4,  4, 5, 6,  6, 6,
      7, 7,  7, 8, 9,  9, 9,

      7, 7,  7, 8, 9,  9, 9,
      7, 7,  7, 8, 9,  9, 9,
      7, 7,  7, 8, 9,  9, 9
                        };
  struct matrix *c = matrix_from(n+4, m+6, expect);
  struct matrix *b = pad_matrix(a, 2, 3);

  if (!matrix_equals(c, b)) {
    matrix_prettyprint(b);
    printf("\n");
    matrix_prettyprint(c);
    printf("Failure\n");
    return 1;
  }

  int32_t expect2[63] = {
      1, 1, 1,  1, 2, 3,  3, 3, 3,
      1, 1, 1,  1, 2, 3,  3, 3, 3,

      1, 1, 1,  1, 2, 3,  3, 3, 3,
      4, 4, 4,  4, 5, 6,  6, 6, 6,
      7, 7, 7,  7, 8, 9,  9, 9, 9,

      7, 7, 7,  7, 8, 9,  9, 9, 9,
      7, 7, 7,  7, 8, 9,  9, 9, 9
    };
  c = matrix_from(n+6, m+4, expect2);
  b = pad_matrix(a, 3, 2);

  if (!matrix_equals(c, b)) {
    matrix_prettyprint(b);
    matrix_prettyprint(c);
    printf("Failure\n");
    return 1;
  }
}
