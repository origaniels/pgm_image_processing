#include <matrix.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct matrix *matrix_new(uint16_t n, uint16_t m) {
  uint16_t *weights = calloc(n * m, sizeof(uint16_t));
  
  return matrix_from(n, m, weights);
}

struct matrix *matrix_from(uint16_t n, uint16_t m, uint16_t *weights) {
  assert(weights);

  struct matrix *res = malloc(sizeof(struct matrix));

  res->n = n;
  res->m = m;
  res->weights = weights;
  
  return res;
}

struct matrix *matmult3x3(struct matrix *a, struct matrix *b, struct matrix *res) {
  assert(a && b && res);

  assert(a->m == b->m);
  assert(a->n == b->n);
  assert(a->n == res->n);
  assert(a->m == res->m);

  assert(a->n == 3);
  assert(a->m == 3);
  assert(a->weights && b->weights && res->weights);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      uint16_t resij = a->weights[i*3 + 0] * b->weights[0*3 + j] +
                      a->weights[i*3 + 1] * b->weights[1*3 + j] +
                      a->weights[i*3 + 2] * b->weights[2*3 + j];
      res->weights[3*i + j] = resij;
    }
  }
}

bool matrix_equals(struct matrix *a, struct matrix *b) {
  assert(a && b);
  assert(a->m == b->m);
  assert(a->n == b->n);
  assert(a->weights && b->weights);

  uint16_t n = a->n;
  uint16_t m = a->m;

  for (int i = 0; i<m; i++) {
    for (int j = 0; j<n; j++) {
      if (b->weights[i*n + j] != a->weights[i*n + j])
        return false;
    }
  }

  return true;
}

void matrix_prettyprint(struct matrix *a) {
  assert(a && a->weights);
  for (int i = 0; i < a->m; i++) {
    printf("|\t");
    for (int j = 0; j < a->n; j++) {
      printf("%d", a->weights[i*a->n+j]);
      printf("\t");
    }
    printf(" |\n");
  }
}
