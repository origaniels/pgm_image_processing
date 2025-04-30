#include <stdbool.h>
#include <stdint.h>

struct matrix {
  // columns
  uint16_t n;
  // rows
  uint16_t m;

  uint16_t *weights;
};

extern struct matrix *matrix_new(uint16_t n, uint16_t m);

extern struct matrix *matrix_from(uint16_t n, uint16_t m, uint16_t *weights);

extern struct matrix *matmult3x3(struct matrix *a, struct matrix *b, struct matrix *res);

extern bool matrix_equals(struct matrix *a, struct matrix *b);

extern void matrix_prettyprint(struct matrix *a);
