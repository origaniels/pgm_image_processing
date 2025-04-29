#include <stdbool.h>
#include <stdint.h>

struct matrix {
  uint8_t n;
  uint8_t m;

  uint16_t *weights;
};

extern struct matrix *matrix_new(uint8_t n, uint8_t m);

extern struct matrix *matrix_from(uint8_t n, uint8_t m, uint16_t *weights);

extern struct matrix *matmult3x3(struct matrix *a, struct matrix *b, struct matrix *res);

extern bool matrix_equals(struct matrix *a, struct matrix *b);

extern void matrix_prettyprint(struct matrix *a);
