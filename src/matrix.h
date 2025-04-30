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

extern struct matrix *convolute(struct matrix *a, struct matrix *kernel);

extern struct matrix *pad_matrix(struct matrix *source_matrix, uint16_t n_padding, uint16_t m_padding);

extern void matrix_prettyprint(struct matrix *a);

extern void fill_section(struct matrix *m, int i_val, int j_val, int i_start, 
  int j_start, int i_end, int j_end);
