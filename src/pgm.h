#include <stdio.h>
#include "matrix.h"

struct pgm {
  uint16_t height;
  uint16_t width;
  uint16_t max_gray;
  uint16_t **rows;
};

extern struct pgm *parse_header(FILE *f);
extern void write_header(FILE *f, uint16_t width, uint16_t height, uint16_t max_value);

extern char skip_whitespaces(FILE *f);

extern void read_bytes_simple(FILE *f, struct pgm *image);
extern void read_bytes_double(FILE *f, struct pgm *image);
extern void write_bytes_simple(FILE *f, struct pgm *image);
extern void write_bytes_double(FILE *f, struct pgm *image);

extern struct matrix *pgm_to_matrix(const char *filename);
extern void matrix_to_pgm(struct matrix *pixels, const char *filename, uint16_t max_gray);

extern void fill_matrix(struct matrix *a, struct pgm *image);
extern struct pgm *matrix_to_struct_pgm(struct matrix *a);
