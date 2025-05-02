#include "pgm.h"

int main() {
  const char *name = "images/bug.pgm";
  const char *name_edges = "bug_blur.pgm";

  struct pgm *image = image_to_pgm(name);
  struct matrix *m = pgm_to_matrix(image);

  int32_t kernel_weights[25] = {
                                -1, -2, -3, -2, -1, 
                                -2, -4, -5, -4, -2, 
                                -3, -5,  68, -5, -3,
                                -2, -4, -5, -4, -2,
                                -1, -2, -3, -2, -1
                              };

  int32_t kernel_weights2[9] = {
                                1, 1, 1,
                                1, 1, 1,
                                1, 1, 1
                              };
  struct matrix *kernel2 = matrix_from(3, 3, kernel_weights2);
  struct matrix *kernel = matrix_from(5, 5, kernel_weights);

  struct matrix *convoled_m = convolve2d(m, kernel2);

  struct pgm *image_edges = matrix_to_pgm(convoled_m, 9 * image->max_gray);
  pgm_to_image(image_edges, name_edges);
}
