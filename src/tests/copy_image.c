#include "pgm.h"

int main() {
  const char *name = "images/grim.pgm";

  struct pgm *image = image_to_pgm(name);
  struct matrix *m = pgm_to_matrix(image);

  struct pgm *image_out = matrix_to_pgm(m, image->max_gray);
  pgm_to_image(image_out, "circle_copy.pgm");  
}