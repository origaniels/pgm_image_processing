#include "include/pgm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define NUM_FILTERS 3


enum filter_type {
  SOBEL,
  LAPLACIAN_3X3,
  LAPLACIAN_5X5,
};

enum filter_type filter = LAPLACIAN_3X3;

int32_t sobel_w_h[9] = {
  1, 0, -1,
  2, 0, -2,
  1, 0, -1
};

int32_t sobel_w_v[9] = {
  1, 2, 1,
  0, 0, 0,
  -1, -2, -1
};

int32_t laplacian_w_5x5[25] = {
  0,  0, -1,  0,  0, 
  0, -1, -2, -1,  0,
 -1, -2, 16, -2, -1,
  0, -1, -2, -1,  0,
  0,  0, -1,  0,  0
};

int32_t laplacian_w_3x3[9] = {
  0, -1,  0,
 -1,  4, -1,
  0, -1,  0
};


void edge_detect(const char *file_in, const char *file_out, enum filter_type type, int block_size) {
  struct pgm *image = image_to_pgm(file_in);
  struct matrix *m = pgm_to_matrix(image);
  
  struct timeval start, end;
  long dif;

  

  struct matrix *convoled_m, *kernel;
  uint8_t inflate_rate = 1;
  if (block_size) {
    switch (type) {
      case SOBEL:
        struct matrix *kernel_sobel_h = matrix_from(3, 3, sobel_w_h);

        struct matrix *kernel_sobel_v = matrix_from(3, 3, sobel_w_v);

        gettimeofday(&start, NULL);
        struct matrix *convoled_m_v = convolve2d_blocked(m, kernel_sobel_v, block_size, block_size);
        struct matrix *convoled_m_h = convolve2d_blocked(m, kernel_sobel_h, block_size, block_size);
        gettimeofday(&end, NULL);
        convoled_m = pythagore_add(convoled_m_v, convoled_m_h);
        inflate_rate = 4;
        break;
      case LAPLACIAN_5X5:
        kernel = matrix_from(5, 5, laplacian_w_5x5);
        gettimeofday(&start, NULL);
        convoled_m = convolve2d_blocked(m, kernel, block_size, block_size);
        gettimeofday(&end, NULL);
        convoled_m = matrix_abs(convoled_m, true);
        
        inflate_rate = 16;
        break;
      case LAPLACIAN_3X3:
        kernel = matrix_from(3, 3, laplacian_w_3x3);
        gettimeofday(&start, NULL);
        convoled_m = convolve2d_blocked(m, kernel, block_size, block_size);
        gettimeofday(&end, NULL);
        convoled_m = matrix_abs(convoled_m, true);

        inflate_rate = 4;
        break;
      default:
        break;
    }
  } else {
    switch (type) {
      case SOBEL:
        struct matrix *kernel_sobel_h = matrix_from(3, 3, sobel_w_h);

        struct matrix *kernel_sobel_v = matrix_from(3, 3, sobel_w_v);

        gettimeofday(&start, NULL);
        struct matrix *convoled_m_v = convolve2d(m, kernel_sobel_v);
        struct matrix *convoled_m_h = convolve2d(m, kernel_sobel_h);
        gettimeofday(&end, NULL);
        convoled_m = pythagore_add(convoled_m_v, convoled_m_h);
        inflate_rate = 4;
        break;
      case LAPLACIAN_5X5:
        kernel = matrix_from(5, 5, laplacian_w_5x5);
        gettimeofday(&start, NULL);
        convoled_m = convolve2d(m, kernel);
        gettimeofday(&end, NULL);
        convoled_m = matrix_abs(convoled_m, true);
        
        inflate_rate = 16;
        break;
      case LAPLACIAN_3X3:
        kernel = matrix_from(3, 3, laplacian_w_3x3);
        gettimeofday(&start, NULL);
        convoled_m = convolve2d(m, kernel);
        gettimeofday(&end, NULL);
        convoled_m = matrix_abs(convoled_m, true);

        inflate_rate = 4;
        break;
      default:
        break;
    }
  }
  
  dif = (end.tv_usec/1000 + end.tv_sec*1000) - (start.tv_usec/1000 + start.tv_sec*1000);
  printf ("%ld\n", dif);

  struct pgm *image_edges = matrix_to_pgm(convoled_m, inflate_rate * image->max_gray);
  pgm_to_image(image_edges, file_out);
}

int main(int argc, char *argv[]) {

  if (argc != 4 && argc != 3) {
    printf("Usage: ./edge_detect [<block_size>] <input_file_name> <output_file_name>\n");
    abort();
  }

  int block_size = 0;
  int idx = 1;
  if (argc==4) {
    block_size = atoi(argv[idx++]);
  }

  const char *in_name = argv[idx++];
  const char *out_name = argv[idx++];

  edge_detect(in_name, out_name, filter, block_size);
}
