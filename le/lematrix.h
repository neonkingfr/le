/* Copyright (c) Kyrylo Polezhaiev and contributors. All rights reserved.
   Released under the MIT license. See LICENSE file in the project root for full license information. */

#include "letensor.h"

#ifndef __LEMATRIX_H__
#define __LEMATRIX_H__

unsigned   le_matrix_get_width            (LeTensor     *matrix);

unsigned   le_matrix_get_height           (LeTensor     *matrix);

float      le_matrix_at                   (LeTensor     *matrix,
                                           unsigned      y,
                                           unsigned      x);

void       le_matrix_set_element          (LeTensor     *matrix,
                                           unsigned      y,
                                           unsigned      x,
                                           float         value);

LeTensor * le_matrix_new_from_data        (unsigned      height,
                                           unsigned      width,
                                           const float  *data);

LeTensor * le_matrix_new_identity         (unsigned      size);

LeTensor * le_matrix_new_uninitialized    (unsigned      height,
                                           unsigned      width);

LeTensor * le_matrix_new_zeros            (unsigned      height,
                                           unsigned      width);

LeTensor * le_matrix_new_rand             (unsigned      height,
                                           unsigned      width);

LeTensor * le_matrix_new_transpose        (LeTensor     *a);

LeTensor * le_matrix_new_product          (LeTensor     *a,
                                           LeTensor     *b);

LeTensor * le_matrix_get_column           (LeTensor     *matrix,
                                           unsigned      x);

#endif
