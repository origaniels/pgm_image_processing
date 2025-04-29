#include <matrix.h>
#include <assert.h>

struct matrix *matrix_init(int n, int m, float *weights) {

}

struct matrix *matmult3x3(struct matrix *a, struct matrix *b, struct matrix *res) {

}

bool equals(struct matrix *a, struct matrix *b) {
  assert(a && b);
  assert(a->m == b->m);
  assert(a->n == b->n);
  assert(a->weights && b->weights);

  int n = a->n;
  int m = a->m;

  for (int i = 0; i<n; i++) {
    for (int j = 0; j<m; j++) {
      if (b->weights[i*n + j] != a->weights[i*n + j])
        return false;
    }
  }

  return true;
}
