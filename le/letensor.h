/* Copyright (c) Kyrylo Polezhaiev and contributors. All rights reserved.
   Released under the MIT license. See LICENSE file in the project root for full license information. */

#include <stdarg.h>
#include <stdbool.h>
#include "letype.h"
#include "leshape.h"

#ifndef __LETENSOR_H__
#define __LETENSOR_H__

LE_BEGIN_DECLS

typedef struct LeTensor LeTensor;

#define LE_TENSOR(tensor) ((LeTensor *)(tensor))

/// @note: Make sure to pass correct number of parameters
LeTensor *         le_tensor_new                           (LeType                  element_type,
                                                            unsigned                num_dimensions,
                                                            ...);

LeTensor *         le_tensor_new_from_va_list              (LeType                  element_type,
                                                            unsigned                num_dimensions,
                                                            va_list                 dims_and_data);

/// @note: Takes ownership of shape and data
LeTensor *         le_tensor_new_from_data                 (LeType                  element_type,
                                                            LeShape *               shape,
                                                            void *                  data);

LeTensor *         le_tensor_new_copy                      (const LeTensor *        another);

/// @note: Takes ownership of shape
LeTensor *         le_tensor_new_rand_f32                  (LeShape *               shape);

LeTensor *         le_tensor_new_cast_f32                  (LeTensor *              tensor);

bool               le_tensor_equal                         (const LeTensor *        a,
                                                            const LeTensor *        b);

bool               le_tensor_reshape                       (LeTensor *              tensor,
                                                            unsigned                num_dimensions,
                                                            ...);

LeTensor *         le_tensor_pick                          (LeTensor *              another,
                                                            uint32_t                index);

LeTensor *         le_tensor_pick_copy                     (const LeTensor *        another,
                                                            uint32_t                index);

uint8_t            le_tensor_at_u8                         (const LeTensor *        tensor,
                                                            uint32_t                index);

float              le_tensor_at_f32                        (const LeTensor *        tensor,
                                                            uint32_t                index);

void               le_tensor_set_f32                       (LeTensor *              tensor,
                                                            uint32_t                index,
                                                            float                   value);

/// @note: a = a + b
void               le_tensor_add                           (LeTensor *              a,
                                                            LeTensor *              b);

/// @note: a = a + b
void               le_tensor_add_f32                       (LeTensor *              a,
                                                            float                   b);

/// @note: a = a - b
void               le_tensor_sub_f32                       (LeTensor *              a,
                                                            float                   b);

/// @note: a = a - b
void               le_tensor_sub_tensor                    (LeTensor *              a,
                                                            const LeTensor *        b);

/// @note: a = a - b
#define le_tensor_sub(a, b) _Generic((b), \
   float: le_tensor_sub_f32, \
   LeTensor *: le_tensor_sub_tensor, \
   const LeTensor *: le_tensor_sub_tensor \
)(a, b)

/// @note: a = a - c * b
void               le_tensor_sub_scaled_f32                (LeTensor *              a,
                                                            float                   c,
                                                            const LeTensor *        b);

/// @note: a = a * b
void               le_tensor_mul_f32                       (LeTensor *              a,
                                                            float                   b);

/// @note: a = a * b
void               le_tensor_mul_tensor                    (LeTensor *              a,
                                                            const LeTensor *        b);

/// @note: a = a * b
#define le_tensor_mul(a, b) _Generic((b), \
   float: le_tensor_mul_f32, \
   LeTensor *: le_tensor_mul_tensor, \
   const LeTensor *: le_tensor_mul_tensor \
)(a, b)

float              le_tensor_sum_f32                       (const LeTensor *        tensor);

void               le_tensor_apply_sigmoid                 (LeTensor *              tensor);

void               le_tensor_apply_sigmoid_prime           (LeTensor *              tensor);

void               le_tensor_apply_tanh                    (LeTensor *              tensor);

void               le_tensor_apply_sqr                     (LeTensor *              tensor);

void               le_tensor_apply_1_minus                 (LeTensor *              tensor);

void               le_tensor_apply_x_minus_sqr_x           (LeTensor *              tensor);

void               le_tensor_apply_gt_f32                  (LeTensor *              tensor,
                                                            float                   scalar);

void               le_tensor_apply_sgn                     (LeTensor *              tensor);

void               le_tensor_apply_relu                    (LeTensor *              tensor);

void               le_tensor_free                          (LeTensor *              tensor);

/** @note: Section Bad */
#include <stdio.h>

LeTensor *         le_scalar_new_f32                       (float                   scalar);

const char *       le_tensor_to_cstr                       (const LeTensor *        tensor);

void               le_tensor_print                         (const LeTensor *        tensor,
                                                            FILE *                  stream);

/** @note: Inner product of two column vectors */
float              le_dot_product                          (const LeTensor *        a,
                                                            const LeTensor *        b);

float              le_rbf                                  (const LeTensor *        a,
                                                            const LeTensor *        b,
                                                            float                   sigma);

typedef struct LeTensorStats
{
   float min;
   float max;
   float mean;
   float deviation;
} LeTensorStats;

LeTensorStats      le_tensor_get_stats                     (LeTensor *              tensor);

LeTensor *         le_tensor_new_equal_u8                  (LeType                  type,
                                                            LeTensor *              tensor,
                                                            uint8_t                 scalar);

LE_END_DECLS

#endif
