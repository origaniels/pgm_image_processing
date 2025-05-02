#include "pgm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_FILTERS 3

enum filter_type {
  SOBEL,
  LAPLACIAN_3X3,
  LAPLACIAN_5X5,
};

void edge_detect(const char *file_in, const char *file_out, enum filter_type type) {
  struct pgm *image = image_to_pgm(file_in);
  struct matrix *m = pgm_to_matrix(image);
  
  clock_t start,end;
  long dif;

  start = clock() / (CLOCKS_PER_SEC / 1000);
  // Do some calculation.
  


  struct matrix *convoled_m, *kernel;
  uint8_t inflate_rate = 1;
  switch (type)
  {
  case SOBEL:
    int32_t sobel_w_h[9] = {
      1, 0, -1,
      2, 0, -2,
      1, 0, -1
    };
    struct matrix *kernel_sobel_h = matrix_from(3, 3, sobel_w_h);

    int32_t sobel_w_v[9] = {
      1, 2, 1,
      0, 0, 0,
      -1, -2, -1
    };
    struct matrix *kernel_sobel_v = matrix_from(3, 3, sobel_w_v);
    struct matrix *convoled_m_v = convolve2d(m, kernel_sobel_v);
    struct matrix *convoled_m_h = convolve2d(m, kernel_sobel_h);
    convoled_m = pythagore_add(convoled_m_v, convoled_m_h);
    inflate_rate = 4;
    break;
  case LAPLACIAN_5X5:
    int32_t kernel_weights_5x5[25] = {
       0,  0, -1,  0,  0, 
       0, -1, -2, -1,  0,
      -1, -2, 16, -2, -1,
       0, -1, -2, -1,  0,
       0,  0, -1,  0,  0
    };
    kernel = matrix_from(5, 5, kernel_weights_5x5);
    convoled_m = convolve2d(m, kernel);
    convoled_m = matrix_abs(convoled_m, true);
    
    inflate_rate = 16;
    break;
  case LAPLACIAN_3X3:
    int32_t kernel_weights_3x3[9] = {
       0, -1,  0,
      -1,  4, -1,
       0, -1,  0
    };
    kernel = matrix_from(3, 3, kernel_weights_3x3);
    convoled_m = convolve2d(m, kernel);
    convoled_m = matrix_abs(convoled_m, true);

    inflate_rate = 4;
    break;
  default:
    break;
  }

  end = clock() / (CLOCKS_PER_SEC / 1000);
  dif = end-start;
  printf ("took %ldms\n", dif );

  struct pgm *image_edges = matrix_to_pgm(convoled_m, inflate_rate * image->max_gray);
  pgm_to_image(image_edges, file_out);
}

int main(int argc, char *argv[]) {

  if (argc != 3) {
    printf("Usage: ./edge_detect <input_file_name> <output_file_name>\n");
    abort();
  }

  const char *in_name = argv[1];
  const char *out_name = argv[2];

  edge_detect(in_name, out_name, SOBEL);
}
