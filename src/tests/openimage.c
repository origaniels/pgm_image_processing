#include "pgm.h"

int main() {
  const char *name = "images/circle.pgm";

  struct matrix *m = pgm_to_matrix(name);

  printf("n: %d\n", m->n);
  printf("m: %d\n", m->m);
  matrix_prettyprint(m);
}