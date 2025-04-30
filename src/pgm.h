#include <stdio.h>
#include "matrix.h"

struct pgm {
  uint16_t height;
  uint16_t width;
  uint16_t max_gray;
  uint16_t **rows;
};

/* Internals */
extern struct pgm *parse_header(FILE *f);
extern void write_header(FILE *f, struct pgm *image);

extern char skip_whitespaces(FILE *f);

extern void read_bytes_simple(FILE *f, struct pgm *image);
extern void read_bytes_double(FILE *f, struct pgm *image);
extern void write_bytes_simple(FILE *f, struct pgm *image);
extern void write_bytes_double(FILE *f, struct pgm *image);

/* pgm/matrix interface */
extern struct matrix *pgm_to_matrix(struct pgm *image);
extern struct pgm *matrix_to_pgm(struct matrix *a, uint16_t max_gray);


/* File/pgm interface */
extern void pgm_to_image(struct pgm *image, const char *filename);
extern struct pgm *image_to_pgm(const char *filename);
