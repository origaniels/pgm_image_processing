#include "pgm.h"

int main() {
  const char *name = "images/circle.pgm";

  struct matrix *m = pgm_to_matrix(name);

  matrix_to_pgm(m, "circle_cpy.pgm", 255);  
}