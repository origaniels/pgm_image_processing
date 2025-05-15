#include "include/matrix.h"

extern struct matrix *pad_matrix(struct matrix *source_matrix, uint16_t n_padding,
                                uint16_t m_padding);

extern int32_t convolve_without_padding(struct matrix *a, struct matrix *kernel, int center_i, int center_j);


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
    and with size n_size, m_size with the value at i_val, j_val. */
inline void fill_section(struct matrix *m, int i_val, int j_val, int i_start, 
      int j_start, int n_size, int m_size) {
  for (int i = i_start; i<i_start+m_size; i++) {
    for (int j = j_start; j<j_start+n_size; j++) {
      m->weights[i*m->n + j] = m->weights[i_val*m->n + j_val];
    }
  }
}

