/**
  *
  */

#ifndef __LEMATRIX_H_
#define __LEMATRIX_H_

typedef struct LeMatrix LeMatrix;

LeMatrix * le_matrix_new          (void);

LeMatrix * le_matrix_new_identity (unsigned size);

LeMatrix * le_matrix_new_zeros    (unsigned height,
                                   unsigned width);

LeMatrix * le_matrix_new_rand     (unsigned height,
                                   unsigned width);

LeMatrix * le_matrix_new_product  (LeMatrix *a,
                                   LeMatrix *b);

void       le_matrix_free         (LeMatrix *matrix);

/** @note: Temporary */
#include <stdio.h>

void       le_matrix_print    (LeMatrix *matrix,
                               FILE     *stream);

#endif
