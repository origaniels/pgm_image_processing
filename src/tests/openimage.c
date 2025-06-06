#include "include/pgm.h"

int main() {
  const char *name = "images/bug.pgm";

  struct pgm *image = image_to_pgm(name);
  struct matrix *m = pgm_to_matrix(image);

  printf("n: %d\n", m->n);
  printf("m: %d\n", m->m);
  matrix_prettyprint(m);
}