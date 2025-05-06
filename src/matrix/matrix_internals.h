#include "include/matrix.h"

extern struct matrix *pad_matrix(struct matrix *source_matrix, uint16_t n_padding,
                                uint16_t m_padding);

struct matrix *extract_matrix_block(struct matrix *source_matrix, int start_i, 
                                  int start_j, int n_size, int m_size);

extern struct matrix *extract_matrix_block_pad(struct matrix *source_matrix, int start_i, 
                        int start_j, int n_size, int m_size, struct matrix *res, int32_t *weights);

extern void fill_section(struct matrix *m, int i_val, int j_val, int i_start,
                        int j_start, int n_size, int m_size);
  