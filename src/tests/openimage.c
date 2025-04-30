#include "pgm.h"

int main() {
  const char *name = "images/circle.pgm";

  struct pgm *image = image_to_pgm(name);
  struct matrix *m = pgm_to_matrix(image);

  printf("n: %d\n", m->n);
  printf("m: %d\n", m->m);
  matrix_prettyprint(m);
}