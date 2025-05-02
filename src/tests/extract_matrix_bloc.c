#include <matrix.h>
#include <stdio.h>

int main() {
  uint16_t n = 5, m = 4;

  int32_t weights[20];
  for (int i = 0; i<20; i++) {
    weights[i] = i+1;
  }

  struct matrix *a = matrix_from(n, m, weights);
  struct matrix *b = extract_matrix_block(a, 1, 4, 1, 3);
  matrix_prettyprint(a);
  printf("\n");
  matrix_prettyprint(b);
}
