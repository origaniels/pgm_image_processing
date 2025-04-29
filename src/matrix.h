#include <stdbool.h>
#include <stdint.h>

struct matrix {
  int n;
  int m;

  uint64_t *weights;
};

extern struct matrix *matrix_init(int n, int m, uint64_t *weights);

extern struct matrix *matmult3x3(struct matrix *a, struct matrix *b, struct matrix *res);

extern bool equals(struct matrix *a, struct matrix *b);
