#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "matrix_internals.h"


/*  Returns element at position (i, j). 
    If the coordinates are outside of the matrix, returns the nearest
    weight. */
inline int32_t matrix_get(struct matrix *a, int i, int j) {
  if ((i > 0 && i < a->m) && (j > 0 && j < a->n)) {
    return a->weights[i * a->n + j];
  }

  /* Coordinates are outside of a. */
  i = i < 0 ? 0 : i;
  j = j < 0 ? 0 : j;
  
  i = i >= a->m ? (a->m - 1) : i;
  j = j >= a->n ? (a->n - 1) : j;

  return a->weights[i * a->n + j];
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
      int32_t resij = a->weights[i*3 + 0] * b->weights[0*3 + j] +
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


int32_t matrix_dot(struct matrix *a, struct matrix *b) {
  assert(a && b);

  assert(a->m == b->m);
  assert(a->n == b->n);

  assert(a->weights && b->weights);

  int32_t res = 0;
  for (int i = 0; i<a->m; i++) {
    for (int j = 0; j<a->n; j++) {
      res += a->weights[i*a->n + j] * b->weights[i*a->n + j];
    }
  }

  return res;
}


struct matrix *matrix_abs(struct matrix *source, bool in_place) {
  struct matrix *res;
  if (in_place) {
    res = source;
  } else {
    res = matrix_new(source->n ,source->m);
  }

  for (int i = 0; i<source->m; i++) {
    for (int j = 0; j<source->n; j++) {
      res->weights[i*source->n + j] = abs(source->weights[i*source->n + j]);
    }
  }
  return res;
}

struct matrix *pythagore_add(struct matrix *a, struct matrix *b) {
  assert(a->n==b->n);
  assert(a->m==b->m);
  struct matrix *res = matrix_new(a->n, a->m);

  for (int i = 0; i<a->m; i++) {
    for (int j = 0; j<a->n; j++) {
      int aij = a->weights[i*a->n+j];
      int bij = b->weights[i*a->n+j];
      res->weights[i*a->n+j] = (int16_t)sqrt(aij * aij + bij * bij);
    }
  }
  return res;
}
