/* Copyright (c) Kyrylo Polezhaiev and contributors. All rights reserved.
   Released under the MIT license. See LICENSE file in the project root for full license information. */

#include <stdarg.h>
#include <stdbool.h>
#include "letype.h"
#include "leshape.h"

#ifndef __LETENSOR_H__
#define __LETENSOR_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LeTensor LeTensor;

#define LE_TENSOR(tensor) ((LeTensor *)(tensor))

/// @note: Make sure to pass correct number of parameters
LeTensor *   le_tensor_new                  (LeType        element_type,
                                             unsigned      num_dimensions,
                                             ...);

LeTensor *   le_tensor_new_from_va_list     (LeType        element_type,
                                             unsigned      num_dimensions,
                                             va_list       dims_and_data);

LeTensor *   le_scalar_new_f32              (float         scalar);

/// @note: Takes ownership of shape
LeTensor *   le_tensor_new_rand_f32         (LeShape      *shape);

/// @note: Takes ownership of shape
LeTensor *   le_tensor_new_from_data        (LeType        element_type,
                                             LeShape      *shape,
                                             void         *data);

LeTensor *   le_tensor_new_copy             (const LeTensor *another);

LeTensor *   le_tensor_new_cast_f32         (LeTensor     *tensor);

LeTensor *   le_tensor_new_f32_equal_u8     (LeTensor     *tensor,
                                             uint8_t       scalar);

bool         le_tensor_equal                (LeTensor     *a,
                                             LeTensor     *b);

bool         le_tensor_reshape              (LeTensor     *tensor,
                                             unsigned      num_dimensions,
                                             ...);

LeTensor *   le_tensor_pick                 (LeTensor     *another,
                                             uint32_t      index);

LeTensor *   le_tensor_pick_copy            (LeTensor     *another,
                                             uint32_t      index);

uint8_t      le_tensor_u8_at                (LeTensor     *tensor,
                                             uint32_t      index);

float        le_tensor_f32_at               (LeTensor     *tensor,
                                             uint32_t      index);

void         le_tensor_f32_set              (LeTensor     *tensor,
                                             uint32_t      index,
                                             float         value);

void         le_tensor_add                  (LeTensor     *matrix,
                                             LeTensor     *another);

void         le_tensor_subtract             (LeTensor     *a,
                                             LeTensor     *b);

void         le_tensor_subtract_scaled      (LeTensor     *a,
                                             float         scale,
                                             LeTensor     *b);

/// @note: a = a * b
void         le_tensor_multiply_by_scalar   (LeTensor     *a,
                                             float         b);

/// @note: a = a * b
void         le_tensor_multiply_elementwise (LeTensor     *a,
                                             LeTensor     *b);

void         le_tensor_add_scalar           (LeTensor     *a,
                                             float         b);

void         le_tensor_subtract_scalar      (LeTensor     *a,
                                             float         b);

float        le_tensor_sum                  (LeTensor     *tensor);

void         le_tensor_apply_sigmoid        (LeTensor     *tensor);

void         le_tensor_apply_sigmoid_prime  (LeTensor     *tensor);

void         le_tensor_apply_tanh           (LeTensor     *tensor);

void         le_tensor_apply_sqr            (LeTensor     *tensor);

void         le_tensor_apply_1_minus        (LeTensor     *tensor);

void         le_tensor_apply_x_minus_sqr_x  (LeTensor     *tensor);

void         le_tensor_apply_greater_than   (LeTensor     *tensor,
                                             float         scalar);

void         le_tensor_apply_svm_prediction (LeTensor     *tensor);

void         le_tensor_apply_relu           (LeTensor     *tensor);

void         le_tensor_free                 (LeTensor     *tensor);

/** @note: Temporary */
#include <stdio.h>

const char * le_tensor_to_cstr              (LeTensor     *tensor);

void         le_tensor_print                (LeTensor     *tensor,
                                             FILE         *stream);

/** @note: Inner product of two column vectors */
float        le_dot_product                 (LeTensor     *a,
                                             LeTensor     *b);

float        le_rbf                         (LeTensor     *a,
                                             LeTensor     *b,
                                             float         sigma);

typedef struct LeTensorStats
{
   float min;
   float max;
   float mean;
   float deviation;
} LeTensorStats;

LeTensorStats le_tensor_get_stats (LeTensor *tensor);

#ifdef __cplusplus
}
#endif

#endif
