/* Copyright (c) Kyrylo Polezhaiev and contributors. All rights reserved.
   Released under the MIT license. See LICENSE file in the project root for full license information. */

#include "lematrix.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "letensor-imp.h"
#ifdef __APPLE__
#include "../platform/accelerate/leaccelerate.h"
#endif

unsigned
le_matrix_get_width(const LeTensor *self)
{
    assert(self->shape->num_dimensions == 2);
    
    return self->shape->sizes[1];
}

unsigned
le_matrix_get_height(const LeTensor *self)
{
    assert(self->shape->num_dimensions == 2);
    
    return self->shape->sizes[0];
}

float
le_matrix_at_f32(const LeTensor *self, unsigned y, unsigned x)
{
    assert(self->element_type == LE_TYPE_FLOAT32);
    assert(self->shape->num_dimensions == 2);
    assert(y < self->shape->sizes[0]);
    assert(x < self->shape->sizes[1]);
    
    return ((float *)self->data)[y * self->shape->sizes[1] + x];
}

double
le_matrix_at_f64(const LeTensor *self, unsigned y, unsigned x)
{
    assert(self->element_type == LE_TYPE_FLOAT64);
    assert(self->shape->num_dimensions == 2);
    assert(y < self->shape->sizes[0]);
    assert(x < self->shape->sizes[1]);
    
    return ((double *)self->data)[y * self->shape->sizes[1] + x];
}

int8_t
le_matrix_at_i8(const LeTensor *self, unsigned y, unsigned x)
{
    assert(self->element_type == LE_TYPE_INT8);
    assert(self->shape->num_dimensions == 2);
    assert(y < self->shape->sizes[0]);
    assert(x < self->shape->sizes[1]);
    
    return ((int8_t *)self->data)[y * self->shape->sizes[1] + x];
}

int16_t
le_matrix_at_i16(const LeTensor *self, unsigned y, unsigned x)
{
    assert(self->element_type == LE_TYPE_INT16);
    assert(self->shape->num_dimensions == 2);
    assert(y < self->shape->sizes[0]);
    assert(x < self->shape->sizes[1]);
    
    return ((int16_t *)self->data)[y * self->shape->sizes[1] + x];
}

int32_t
le_matrix_at_i32(const LeTensor *self, unsigned y, unsigned x)
{
    assert(self->element_type == LE_TYPE_INT32);
    assert(self->shape->num_dimensions == 2);
    assert(y < self->shape->sizes[0]);
    assert(x < self->shape->sizes[1]);
    
    return ((int32_t *)self->data)[y * self->shape->sizes[1] + x];
}

void
le_matrix_add(LeTensor *self, const LeTensor *another)
{
    unsigned x, y;
    
    assert(self->shape->num_dimensions == 2);
    
    /// @note: Add horizontal broadcasting
    assert(self->shape->sizes[0] == another->shape->sizes[0]);
    assert(another->shape->sizes[1] == 1);
    
    for (y = 0; y < self->shape->sizes[0]; y++)
    {
        for (x = 0; x < self->shape->sizes[1]; x++)
        {
            ((float *)self->data)[y * self->shape->sizes[1] + x] += ((float *)another->data)[y];
        }
    }
}

void
le_matrix_set_i8(LeTensor *self, unsigned y, unsigned x, int8_t value)
{
    assert(self->element_type == LE_TYPE_INT8);
    assert(self->shape->num_dimensions == 2);
    
    assert(y < self->shape->sizes[0]);
    assert(x < self->shape->sizes[1]);
    
    ((int8_t *)self->data)[y * self->shape->sizes[1] + x] = value;
}

void
le_matrix_set_u8(LeTensor *self, unsigned y, unsigned x, uint8_t value)
{
    assert(self->element_type == LE_TYPE_UINT8);
    assert(self->shape->num_dimensions == 2);
    
    assert(y < self->shape->sizes[0]);
    assert(x < self->shape->sizes[1]);
    
    ((uint8_t *)self->data)[y * self->shape->sizes[1] + x] = value;
}

void
le_matrix_set_i16(LeTensor *self, unsigned y, unsigned x, int16_t value)
{
    assert(self->element_type == LE_TYPE_INT16);
    assert(self->shape->num_dimensions == 2);
    
    assert(y < self->shape->sizes[0]);
    assert(x < self->shape->sizes[1]);
    
    ((int16_t *)self->data)[y * self->shape->sizes[1] + x] = value;
}

void
le_matrix_set_u16(LeTensor *self, unsigned y, unsigned x, uint16_t value)
{
    assert(self->element_type == LE_TYPE_UINT16);
    assert(self->shape->num_dimensions == 2);
    
    assert(y < self->shape->sizes[0]);
    assert(x < self->shape->sizes[1]);
    
    ((uint16_t *)self->data)[y * self->shape->sizes[1] + x] = value;
}

void
le_matrix_set_i32(LeTensor *self, unsigned y, unsigned x, int32_t value)
{
    assert(self->element_type == LE_TYPE_INT32);
    assert(self->shape->num_dimensions == 2);
    
    assert(y < self->shape->sizes[0]);
    assert(x < self->shape->sizes[1]);
    
    ((int32_t *)self->data)[y * self->shape->sizes[1] + x] = value;
}

void
le_matrix_set_u32(LeTensor *self, unsigned y, unsigned x, uint32_t value)
{
    assert(self->element_type == LE_TYPE_UINT32);
    assert(self->shape->num_dimensions == 2);
    
    assert(y < self->shape->sizes[0]);
    assert(x < self->shape->sizes[1]);
    
    ((uint32_t *)self->data)[y * self->shape->sizes[1] + x] = value;
}

void
le_matrix_set_f16(LeTensor *self, unsigned y, unsigned x, half value)
{
    assert(self->element_type == LE_TYPE_FLOAT16);
    assert(self->shape->num_dimensions == 2);
    
    assert(y < self->shape->sizes[0]);
    assert(x < self->shape->sizes[1]);
    
    ((half *)self->data)[y * self->shape->sizes[1] + x] = value;
}

void
le_matrix_set_f32(LeTensor *self, unsigned y, unsigned x, float value)
{
    assert(self->element_type == LE_TYPE_FLOAT32);
    assert(self->shape->num_dimensions == 2);
    
    assert(y < self->shape->sizes[0]);
    assert(x < self->shape->sizes[1]);
    
    ((float *)self->data)[y * self->shape->sizes[1] + x] = value;
}

void
le_matrix_set_f64(LeTensor *self, unsigned y, unsigned x, double value)
{
    assert(self->element_type == LE_TYPE_FLOAT64);
    assert(self->shape->num_dimensions == 2);
    
    assert(y < self->shape->sizes[0]);
    assert(x < self->shape->sizes[1]);
    
    ((double *)self->data)[y * self->shape->sizes[1] + x] = value;
}

LeTensor *
le_matrix_new_identity(LeType type, unsigned size)
{
    unsigned x;
    unsigned y;
    LeTensor *self;
    
    self = malloc(sizeof(struct LeTensor));
    self->element_type = LE_TYPE_FLOAT32;
    self->shape = le_shape_new(2, size, size);
    self->stride = size;
    self->owns_data = true;
    self->data = malloc(size * size * sizeof(float));
    
    for (y = 0; y < size; y++)
    {
        for (x = 0; x < size; x++)
        {
            switch (type)
            {
            case LE_TYPE_INT8:
                ((int8_t *)self->data)[y * size + x] = (x == y) ? 1 : 0;
                break;
            case LE_TYPE_UINT8:
                ((uint8_t *)self->data)[y * size + x] = (x == y) ? 1 : 0;
                break;
            case LE_TYPE_INT16:
                ((int16_t *)self->data)[y * size + x] = (x == y) ? 1 : 0;
                break;
            case LE_TYPE_UINT16:
                ((uint16_t *)self->data)[y * size + x] = (x == y) ? 1 : 0;
                break;
            case LE_TYPE_INT32:
                ((int32_t *)self->data)[y * size + x] = (x == y) ? 1 : 0;
                break;
            case LE_TYPE_UINT32:
                ((uint32_t *)self->data)[y * size + x] = (x == y) ? 1 : 0;
                break;
            case LE_TYPE_FLOAT16:
                ((uint16_t *)self->data)[y * size + x] = (x == y) ? F16_1 : F16_0;
                break;
            case LE_TYPE_FLOAT32:
                ((float *)self->data)[y * size + x] = (x == y) ? 1.0f : 0.0f;
                break;
            case LE_TYPE_FLOAT64:
                ((double *)self->data)[y * size + x] = (x == y) ? 1.0 : 0.0;
                break;
            case LE_TYPE_VOID:
            default:
                break;
            }
        }
    }
    
    return self;
}

LeTensor *
le_matrix_new_uninitialized(LeType type, unsigned height, unsigned width)
{
    LeTensor *self;
    
    self = malloc(sizeof(struct LeTensor));
    self->element_type = type;
    self->shape = le_shape_new(2, height, width);
    self->stride = width;
    self->owns_data = true;
    self->data = malloc(height * width * le_type_size(self->element_type));
    
    return self;
}

LeTensor *
le_matrix_new_zeros(LeType type, unsigned height, unsigned width)
{
    unsigned i;
    unsigned elements_count;
    LeTensor *self;
    
    self = malloc(sizeof(struct LeTensor));
    self->shape = le_shape_new(2, height, width);
    self->element_type = LE_TYPE_FLOAT32;
    self->stride = width;
    self->owns_data = true;
    self->data = malloc(height * width * sizeof(float));
    elements_count = height * width;
    
    for (i = 0; i < elements_count; i++)
    {
        ((float *)self->data)[i] = 0.0f;
    }
    
    return self;
}


LeTensor *
le_matrix_new_rand_f32(unsigned height, unsigned width)
{
    unsigned i;
    unsigned elements_count;
    LeTensor *self;
    
    self = malloc(sizeof(struct LeTensor));
    self->element_type = LE_TYPE_FLOAT32;
    self->shape = le_shape_new(2, height, width);
    self->stride = width;
    self->owns_data = true;
    elements_count = height * width;
    self->data = malloc(elements_count * sizeof(float));
    
    for (i = 0; i < elements_count; i++)
    {
        ((float *)self->data)[i] = rand() / (float)RAND_MAX;
    }
    
    return self;
}

#define TRNASPOSE(type) for (y = 0; y < self->shape->sizes[0]; y++) \
{ \
    for (x = 0; x < self->shape->sizes[1]; x++) \
    { \
        ((type *)self->data)[y * self->shape->sizes[1] + x] = ((type *)a->data)[x * a->shape->sizes[1] + y]; \
    } \
}

LeTensor *
le_matrix_new_transpose(LeTensor *a)
{
    /// @todo: Take stride into account
    assert(a->shape->num_dimensions == 2);

    unsigned x;
    unsigned y;
    LeTensor *self;
    
    self = malloc(sizeof(struct LeTensor));
    self->element_type = a->element_type;
    self->shape = le_shape_new(2, a->shape->sizes[1], a->shape->sizes[0]);
    self->stride = le_shape_get_last_size(self->shape);
    self->owns_data = true;
    self->data = malloc(le_shape_get_elements_count(self->shape) * le_type_size(self->element_type));
    
    switch (le_type_size(self->element_type))
    {
    case 1:
        TRNASPOSE(uint8_t);
        break;

    case 2:
        TRNASPOSE(uint16_t);
        break;

    case 4:
        TRNASPOSE(uint32_t);
        break;

    case 8:
        TRNASPOSE(uint64_t);
        break;

    default:
        break;
    }
    
    return self;
}

#undef TRANSPOSE


LeTensor *
le_matrix_new_sum(const LeTensor *a, unsigned dimension)
{
    /// @todo: Take stride into account
    unsigned x, y;
    
    assert(a->shape->num_dimensions == 2);

    LeTensor *self;
    
    self = malloc(sizeof(struct LeTensor));
    self->element_type = LE_TYPE_FLOAT32;
    self->shape = le_shape_new(2, a->shape->sizes[0], 1/*a->shape->sizes[1]*/);
    self->stride = le_shape_get_last_size(self->shape);
    self->owns_data = true;
    self->data = malloc(le_shape_get_elements_count(self->shape) * le_type_size(self->element_type));
    
    assert(/*(dimension == 0) || */(dimension == 1));
    for (y = 0; y < a->shape->sizes[0]; y++)
    {
        ((float *)self->data)[y] = 0.0f;
        for (x = 0; x < a->shape->sizes[1]; x++)
        {
            ((float *)self->data)[y] += ((float *)a->data)[y * a->shape->sizes[1] + x];
        }
    }

    return self;
}

LeTensor *
le_matrix_new_one_hot(LeType type, const LeTensor *a, unsigned num_classes)
{
    /// @todo: Take stride into account
    assert(a->shape->num_dimensions == 2);
    assert(a->shape->sizes[0] == 1);
    
    unsigned example, klass;
    LeTensor *self;
    
    self = malloc(sizeof(struct LeTensor));
    self->element_type = type;
    self->shape = le_shape_new(2, num_classes, a->shape->sizes[1]);
    self->stride = le_shape_get_last_size(self->shape);
    self->owns_data = true;
    self->data = malloc(le_shape_get_elements_count(self->shape) * le_type_size(self->element_type));
    
    for (example = 0; example < a->shape->sizes[1]; example++)
    {
        for (klass = 0; klass < num_classes; klass++)
        {
            bool hot = (klass == le_tensor_at_u8(a, example));
            switch (type)
            {
            case LE_TYPE_INT8:
                le_matrix_set_i8(self, klass, example, hot ? 1 : 0);
                break;
            case LE_TYPE_UINT8:
                le_matrix_set_u8(self, klass, example, hot ? 1 : 0);
                break;
            case LE_TYPE_INT16:
                le_matrix_set_i16(self, klass, example, hot ? 1 : 0);
                break;
            case LE_TYPE_UINT16:
                le_matrix_set_u16(self, klass, example, hot ? 1 : 0);
                break;
            case LE_TYPE_INT32:
                le_matrix_set_i32(self, klass, example, hot ? 1 : 0);
                break;
            case LE_TYPE_UINT32:
                le_matrix_set_u32(self, klass, example, hot ? 1 : 0);
                break;
            case LE_TYPE_FLOAT16:
                le_matrix_set_f16(self, klass, example, hot ? F16_1 : F16_0);
                break;
            case LE_TYPE_FLOAT32:
                le_matrix_set_f32(self, klass, example, hot ? 1.0f : 0.0f);
                break;
            case LE_TYPE_FLOAT64:
                le_matrix_set_f32(self, klass, example, hot ? 1.0 : 0.0);
                break;
            case LE_TYPE_VOID:
            default:
                break;
            }
        }
    }

    return self;
}

LeTensor *
le_matrix_new_product(const LeTensor *a, const LeTensor *b)
{
    return le_matrix_new_product_full(a, false, b, false);
}

LeTensor *
le_matrix_new_product_full(const LeTensor *a, bool transpose_a, const LeTensor *b, bool transpose_b)
{
    /// @todo: Take stride into account
#ifdef __APPLE__
    return le_accelerate_matrix_new_product(a, transpose_a, b, transpose_b);
#else
    assert(a->shape->num_dimensions == 2);
    assert(b->shape->num_dimensions == 2);

    unsigned x;
    unsigned y;
    unsigned i;
    
    LeTensor *self;
    
    assert(a->element_type == b->element_type);
    
    unsigned a_width = transpose_a ? a->shape->sizes[0] : a->shape->sizes[1];
    unsigned a_height = transpose_a ? a->shape->sizes[1] : a->shape->sizes[0];
    unsigned b_width = transpose_b ? b->shape->sizes[0] : b->shape->sizes[1];
    unsigned b_height = transpose_b ? b->shape->sizes[1] : b->shape->sizes[0];
    
    assert(a_width == b_height);
            
    self = malloc(sizeof(struct LeTensor));
    self->element_type = a->element_type;
    self->shape = le_shape_new(2, a_height, b_width);
    self->stride = le_shape_get_last_size(self->shape);
    self->owns_data = true;
    self->data = malloc(le_shape_get_elements_count(self->shape) * sizeof(float));
    
    for (y = 0; y < a_height; y++)
    {
        for (x = 0; x < b_width; x++)
        {
            size_t index = y * b_width + x;
            ((float *)self->data)[index] = 0.0f;
            for (i = 0; i < a_width; i++)
            {
                /// @note: Check indices
                size_t a_index = transpose_a ? i * a_height + y : y * a_width + i;
                float a_element = ((float *)a->data)[a_index];
                size_t b_index = transpose_b ? x * b_height + i : i * b_width + x;
                float b_element = ((float *)b->data)[b_index];
                float prod = a_element * b_element;
                ((float *)self->data)[index] += prod;
            }
        }
    }
    
    return self;
#endif
}

LeTensor *
le_matrix_new_conv2d(const LeTensor *image, const LeTensor *filter)
{
    assert(image->shape->num_dimensions == 2);
    assert(filter->shape->num_dimensions == 2);
    
    assert(image->element_type == LE_TYPE_FLOAT32);
    assert(filter->element_type == LE_TYPE_FLOAT32);

    int32_t fh = le_matrix_get_height(filter);
    int32_t height = le_matrix_get_height(image) - fh + 1;
    int32_t fw = le_matrix_get_width(filter);
    int32_t width = le_matrix_get_width(image) - le_matrix_get_width(filter) + 1;

    assert(height > 1);
    assert(width > 1);

    LeTensor *self = malloc(sizeof(struct LeTensor));
    self->element_type = image->element_type;
    self->shape = le_shape_new(2, height, width);
    self->stride = le_shape_get_last_size(self->shape);
    self->owns_data = true;
    self->data = malloc(le_shape_get_elements_count(self->shape) * sizeof(float));

    for (int32_t oy = 0; oy < height; oy++)
    {
        for (int32_t ox = 0; ox < width; ox++)
        {
            float value = 0.0f;
            for (int32_t fy = 0; fy < fh; fy++)
            {
                for (int32_t fx = 0; fx < fw; fx++)
                {
                    value += le_matrix_at_f32(image, oy + fy, ox + fx) * le_matrix_at_f32(filter, fy, fx);
                }
            }
            le_matrix_set(self, oy, ox, value);
        }
    }
    
    return self;
}


LeTensor *
le_matrix_get_column(const LeTensor *matrix, unsigned x)
{
    /// @todo: Take stride into account
    assert(matrix->shape->num_dimensions == 2);
    
    LeTensor *self = malloc(sizeof(struct LeTensor));
    self->element_type = matrix->element_type;
    self->shape = le_shape_new(2, matrix->shape->sizes[0], 1);
    self->stride = matrix->stride;

    self->owns_data = false;
    self->data = matrix->data + x * le_type_size(self->element_type);
    
    return self;
}
                  
LeTensor *
le_matrix_get_column_copy(const LeTensor *self, unsigned x)
{
    /// @todo: Take stride into account
    assert(self->shape->num_dimensions == 2);
    /// @todo: Add dimension checks
    
    unsigned y;
    unsigned height = le_matrix_get_height(self);
    LeTensor *column = le_matrix_new_uninitialized(self->element_type, height, 1);
    
    for (y = 0; y < height; y++)
    {
        ((float *)column->data)[y] = ((float *)self->data)[y * self->shape->sizes[1] + x];
    }
    
    return column;
}

void
le_matrix_apply_softmax(LeTensor *self)
{
    assert(self->shape->num_dimensions == 2);

    /// @todo: Take stride into account
    unsigned example, klass;
    unsigned num_classes = self->shape->sizes[0];
    unsigned num_examples = self->shape->sizes[1];

    for (example = 0; example < num_examples; example++)
    {
        float max = -INFINITY;
        for (klass = 0; klass < num_classes; klass++)
        {
            float value = le_matrix_at_f32(self, klass, example);
            if (value > max)
            {
                max = value;
            }
        }
        float sum = 0;
        for (klass = 0; klass < num_classes; klass++)
        {
            float activation = expf(le_matrix_at_f32(self, klass, example) - max);
            sum += activation;
            le_matrix_set(self, klass, example, activation);
        }
        for (klass = 0; klass < num_classes; klass++)
        {
            float activation = le_matrix_at_f32(self, klass, example);
            activation /= sum;
            le_matrix_set(self, klass, example, activation);
        }
    }
}

void
le_matrix_apply_softmax_prime(LeTensor *self)
{
    assert(self->shape->num_dimensions == 2);
    assert(self->shape->num_dimensions == 2);

    le_matrix_apply_softmax(self);

    unsigned elements_count = le_shape_get_elements_count(self->shape);
    
    for (unsigned i = 0; i < elements_count; i++)
    {
        float s = ((float *)self->data)[i];
        ((float *)self->data)[i] = s * (1.0f - s);
    }
}
