#include <stdlib.h>
#include <assert.h>

#include "matrix_internals.h"

struct matrix *matrix_new(uint16_t n, uint16_t m) {
  int32_t *weights = calloc(n * m, sizeof(int32_t));
  
  return matrix_from(n, m, weights);
}

struct matrix *matrix_from(uint16_t n, uint16_t m, int32_t *weights) {
  assert(weights);

  struct matrix *res = malloc(sizeof(struct matrix));

  res->n = n;
  res->m = m;
  res->weights = weights;
  
  return res;
}

void matrix_from_inplace(struct matrix *res, uint16_t n, uint16_t m, int32_t *weights) {
  assert(weights);
  assert(res);

  res->n = n;
  res->m = m;
  res->weights = weights;
}
