#include <stdio.h>
#include "matrix.h"

struct pgm {
  uint16_t height;
  uint16_t width;
  uint16_t max_gray;
  uint16_t **rows;
};

/* pgm/matrix interface */
extern struct matrix *pgm_to_matrix(struct pgm *image);
extern struct pgm *matrix_to_pgm(struct matrix *a, uint16_t max_gray);


/* File/pgm interface */
extern void pgm_to_image(struct pgm *image, const char *filename);
extern struct pgm *image_to_pgm(const char *filename);
