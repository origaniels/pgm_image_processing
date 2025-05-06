#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "matrix_internals.h"

/*  pads the input matrix to fit the shape extended by the provided padding.
    padding copies the edge value. Padding is done on both sides symetrically. */
struct matrix *pad_matrix(struct matrix *source_matrix, uint16_t n_padding, uint16_t m_padding) {
  uint16_t n = source_matrix->n;
  uint16_t m = source_matrix->m;
  struct matrix *res = matrix_new(n + 2 * n_padding, m + 2 * m_padding);

  /* fill inner values */
  for (int i = m_padding; i<m_padding+m; i++) {
    int32_t *dst = &res->weights[i * res->n + n_padding];
    int32_t *src = &source_matrix->weights[(i-m_padding) * n];
    memcpy(dst, src, n * sizeof(int32_t));
  }

  /* do padding */
  
  /* corners */
  fill_section(res, m_padding, n_padding, 0, 0, n_padding, m_padding); /* top left corner */

  fill_section(res, m_padding, res->n-n_padding-1, 0, res->n-n_padding,
              n_padding, m_padding); /* top right corner */
  
  fill_section(res, res->m-m_padding-1, res->n-n_padding-1,
              res->m-m_padding, res->n-n_padding, n_padding, m_padding); /* bottom right corner */
  
  fill_section(res, res->m-m_padding-1, n_padding, res->m-m_padding, 0,
    n_padding, m_padding); /* bottom left corner */
  
  /* edges */
  /* top */
  for (int j = n_padding; j<res->n-n_padding; j++) {
    fill_section(res, m_padding, j, 0, j, 1, m_padding);
  }

  /* bottom */
  for (int j = n_padding; j<res->n-n_padding; j++) {
    fill_section(res, res->m-m_padding-1, j, res->m-m_padding, j, 1, m_padding);
  }

  /* left */
  for (int i = m_padding; i<res->m-m_padding; i++) {
    fill_section(res, i, n_padding, i, 0, n_padding, 1);
  }

  /* right */
  for (int i = m_padding; i<res->m-m_padding; i++) {
    fill_section(res, i, res->n-n_padding-1, i, res->n-n_padding, n_padding, 1);
  }

  return res;
}

/*  Fills the rectangular section of the matrix bound by i_start, j_start 
    and with size n_size, m_size with the value at i_val, j_val. */
inline void fill_section(struct matrix *m, int i_val, int j_val, int i_start, 
                        int j_start, int n_size, int m_size) {
  for (int i = i_start; i<i_start+m_size; i++) {
    for (int j = j_start; j<j_start+n_size; j++) {
      m->weights[i*m->n + j] = m->weights[i_val*m->n + j_val];
    }
  }
}

inline struct matrix *extract_matrix_block(struct matrix *source_matrix, int start_i, 
                                  int start_j, int n_size, int m_size) {
    assert(start_i+m_size <= source_matrix->m);
    assert(start_j+n_size <= source_matrix->n);

    int32_t *weights = malloc(m_size * n_size * sizeof(int32_t));
    int bloc_i = 0;
    for (int i = start_i; i<start_i+m_size; i++) {
      int bloc_j = 0;
      for (int j = start_j; j<start_j+n_size; j++) {
        weights[bloc_i*n_size + bloc_j] = source_matrix->weights[i*source_matrix->n+j];
        bloc_j++;
      }
      bloc_i++;
    }
    struct matrix *res = matrix_from(n_size, m_size, weights);
    return res;
}

/*  Fills the rectangular section of the matrix bound by i_start, j_start 
    and with size n_size, m_size with the value at i_val, j_val. 
    This implementation allows start_i (resp. start_j) to be either negative
    or too close to the boundaries of source_matrix with regards to m_size 
    (resp. n_size). */
inline struct matrix *extract_matrix_block_pad(struct matrix *source_matrix, int start_i, 
  int start_j, int n_size, int m_size, struct matrix *res, int32_t *weights) {
        
  if (!weights) {
    weights = malloc(m_size * n_size * sizeof(int32_t));
  }
  
  bool cond_i = start_i+m_size <= source_matrix->m || start_i < 0;
  bool cond_j = start_j+n_size <= source_matrix->n || start_j < 0;

  if (cond_i || cond_j) {
    /* requested block steps out of the boundaries of source_matrix. */
    int source_i, source_j;
    int bloc_i = 0;
    for (int i = start_i; i<start_i+m_size; i++) {
      int bloc_j = 0;
      source_i = i<0 ? 0 : (i>=source_matrix->m ? source_matrix->m-1 : i);

      
      for (int j = start_j; j<start_j+n_size; j++) {
        source_j = j<0 ? 0 : (j>=source_matrix->n ? source_matrix->n-1 : j);

        weights[bloc_i*n_size + bloc_j] = source_matrix->weights[source_i*source_matrix->n+source_j];
        bloc_j++;
      }
      bloc_i++;
    }

  } else {
    /* Requested block is fully contained by source_matrix. */
    int bloc_i = 0;
    for (int i = start_i; i<start_i+m_size; i++) {
      int bloc_j = 0;
      for (int j = start_j; j<start_j+n_size; j++) {
        weights[bloc_i*n_size + bloc_j] = source_matrix->weights[i*source_matrix->n+j];
        bloc_j++;
      }
      bloc_i++;
    }
  }

  if (!res) {
    res = matrix_from(n_size, m_size, weights);
  } else {
    matrix_from_inplace(res, n_size, m_size, weights);
  }

  return res;
}

int32_t convolve(struct matrix *a, struct matrix *b) {
  assert(a && b);

  assert(a->m == b->m);
  assert(a->n == b->n);

  assert(a->weights && b->weights);

  int32_t res = 0;
  for (int i = 0; i<a->m; i++) {
    for (int j = 0; j<a->n; j++) {
      res += a->weights[i*a->n + j] * b->weights[(a->m-i-1)*a->n + (a->n-j-1)];
    }
  }
  return res;
}

int32_t convolve_without_padding(struct matrix *a, struct matrix *b) {
  assert(a && b);

  assert(a->m == b->m);
  assert(a->n == b->n);

  assert(a->weights && b->weights);

  int32_t res = 0;
  for (int i = 0; i<a->m; i++) {
    for (int j = 0; j<a->n; j++) {
      uint16_t a_idx = i*a->n + j;
      uint16_t b_idx = (a->m-i-1)*a->n + (a->n-j-1);
      res += a->weights[a_idx] * b->weights[b_idx];
    }
  }
  return res;
}

/*  performs the 2D convolution on matrix a by kernel.
    kernel is slid over a and performs matrix convolution on each
    sub_block of a. */
struct matrix *convolve2d(struct matrix *a, struct matrix *kernel) {
  uint16_t n_padding = kernel->n / 2;
  uint16_t m_padding = kernel->m / 2;

  struct matrix *res = matrix_new(a->n, a->m);

  for (int i = 0; i<res->m; i++) {

    /* left side */
    for (int j = 0; j<n_padding; j++) {
      struct matrix *block = extract_matrix_block_pad(a, i-m_padding, j-n_padding, kernel->n, kernel->m, NULL, NULL);
      res->weights[i*res->n + j] = convolve(block, kernel);
    }

    /* right side */
    for (int j = res->n-n_padding; j<res->n; j++) {
      struct matrix *block = extract_matrix_block_pad(a, i-m_padding, j-n_padding, kernel->n, kernel->m, NULL, NULL);
      res->weights[i*res->n + j] = convolve(block, kernel);
    }
  }


  /* inner values*/
  for (int i = 0; i<res->m; i++) {
    for (int j = n_padding; j<res->n-n_padding; j++) {
      struct matrix *block = extract_matrix_block_pad(a, i-m_padding, j-n_padding, kernel->n, kernel->m, NULL, NULL);
      res->weights[i*res->n + j] = convolve(block, kernel);
    }
  }
  return res;
}

/*  Processes the 2dconvolution of matrix a by the provided kernel. 
    Processing is done block by block according to the sizes provided. */
struct matrix *convolve2d_blocked(struct matrix *a, struct matrix *kernel, uint16_t block_size_n, uint16_t block_size_m) {
  /* expand a to fit the kernel everywhere */
  uint16_t n_padding = kernel->n / 2;
  uint16_t m_padding = kernel->m / 2;

  struct matrix *res = matrix_new(a->n, a->m);

  uint16_t num_blocks_n = a->n/block_size_n;
  uint16_t num_blocks_m = a->m/block_size_m;

  /* If there is a remainder, add an extra block. */
  uint16_t rem_n = a->n % block_size_n;
  uint16_t rem_m = a->m % block_size_m;
  if (rem_n) {
    num_blocks_n++;
  }
  if (rem_m) {
    num_blocks_m++;
  }

  struct matrix *blocks = malloc(num_blocks_m * num_blocks_n * sizeof(struct matrix));
  int32_t *blocks_weights = malloc(((num_blocks_m - 1) * (num_blocks_n - 1)
                                   * (block_size_m + 2 * m_padding)
                                   * (block_size_n + 2 * n_padding)
                                   + num_blocks_n * (rem_m + 2 * m_padding) 
                                   + num_blocks_m * (rem_n + 2 * n_padding)
                                  ) * sizeof(int32_t));

  for (int I = 0; I<num_blocks_m; I++) {
    uint16_t cur_block_size_m = block_size_m;
    if (I==num_blocks_m-1) {
      cur_block_size_m = rem_m;
    }
    uint16_t padded_block_size_m = cur_block_size_m + 2 * m_padding;

    for (int J = 0; J<num_blocks_n; J++) {
      uint16_t cur_block_size_n = block_size_n;
      if (J==num_blocks_n-1) {
        cur_block_size_n = rem_n;
      }

      uint16_t padded_block_size_n = cur_block_size_n + 2 * n_padding;

      struct matrix *block = extract_matrix_block_pad(a, I * block_size_m-m_padding, J * block_size_n-n_padding,
                                                     padded_block_size_n, padded_block_size_m,
                                                     &blocks[I * num_blocks_n +J], 
                                                     &blocks_weights[I * num_blocks_n * block_size_m + J * block_size_n]);
      
      uint16_t i_upperbound = cur_block_size_m;
      for (int i = 0; i < i_upperbound; i++) {
        uint16_t j_upperbound = cur_block_size_n;

        for (int j = 0; j < j_upperbound; j++) {
          struct matrix *inner_block = extract_matrix_block(block, i, j, kernel->n, kernel->m);

          uint16_t res_i = I * block_size_m + i;
          uint16_t res_j = J * block_size_n + j;

          res->weights[res_i*res->n + res_j] = convolve(inner_block, kernel);
        }
      }
    }
  }

  return res;
}
