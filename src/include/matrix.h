#include <stdbool.h>
#include <stdint.h>

struct matrix {
  // columns
  uint16_t n;
  // rows
  uint16_t m;

  int32_t *weights;
};

extern struct matrix *matrix_new(uint16_t n, uint16_t m);
extern struct matrix *matrix_from(uint16_t n, uint16_t m, int32_t *weights);
extern void matrix_from_inplace(struct matrix *res, uint16_t n, uint16_t m, int32_t *weights);

extern struct matrix *matmult3x3(struct matrix *a, struct matrix *b, struct matrix *res);

extern bool matrix_equals(struct matrix *a, struct matrix *b);

extern struct matrix *matrix_abs(struct matrix *source, bool in_place);

struct matrix *pythagore_add(struct matrix *a, struct matrix *b);

extern int32_t convolve(struct matrix *a, struct matrix *b);

extern struct matrix *convolve2d(struct matrix *a, struct matrix *kernel);

extern struct matrix *convolve2d_blocked(struct matrix *a, struct matrix *kernel, uint16_t block_size_n, uint16_t block_size_m);

extern int32_t matrix_dot(struct matrix *a, struct matrix *b);

extern void matrix_prettyprint(struct matrix *a);



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
    