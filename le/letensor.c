/* Copyright (c) Kyrylo Polezhaiev and contributors. All rights reserved.
   Released under the MIT license. See LICENSE file in the project root for full license information. */

#include "letensor.h"
#include "letensor-imp.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

LeTensor *
le_matrix_new(void)
{
    LeTensor *self = malloc(sizeof(struct LeTensor));
    self->data = NULL;
    self->shape = NULL;
    self->element_type = LE_TYPE_VOID;
    return self;
}

LeTensor *
le_matrix_new_copy(LeTensor *another)
{
    LeTensor *self = malloc(sizeof(struct LeTensor));
    self->element_type = another->element_type;
    size_t data_size = le_shape_get_elements_count(another->shape) * le_type_size(self->element_type);
    self->data = malloc(data_size);
    memcpy(self->data, another->data, data_size);
    self->shape = le_shape_copy(another->shape);
    return self;
}

LeTensor *
le_matrix_new_from_data(unsigned height, unsigned width, const float *data)
{
    LeTensor *self;
    size_t data_size = height * width * sizeof(float);
    
    self = malloc(sizeof(struct LeTensor));
    self->data = malloc(data_size);
    self->shape = le_shape_new(2, height, width);
    self->element_type = LE_TYPE_FLOAT32;
    memcpy(self->data, data, data_size);
    
    return self;
}

void
le_matrix_set_element(LeTensor *self, unsigned y, unsigned x, float value)
{
    assert(self->shape->num_dimensions == 2);
    
    assert(y < self->shape->sizes[0]);
    assert(x < self->shape->sizes[1]);
    
    self->data[y * self->shape->sizes[1] + x] = value;
}

void
le_matrix_empty(LeTensor *self)
{
    free(self->data);
    self->data = NULL;
    free(self->shape);
    self->shape = NULL;
    self->element_type = LE_TYPE_VOID;
}

float
le_dot_product(LeTensor *a, LeTensor *b)
{
    assert(a->shape->num_dimensions == 2);
    assert(b->shape->num_dimensions == 2);
    
    unsigned y;
    
    float result = 0;

    /** @todo: Test results against transposed a multiplied by b */
    if (a->shape->sizes[0] != b->shape->sizes[0] || a->shape->sizes[1] != 1 || b->shape->sizes[1] != 1)
        return nanf("");
    
    for (y = 0; y < a->shape->sizes[0]; y++)
    {
        /** @note: This addressing is correct as we
            ensured that widths of both matrices
            (supposed to be column vectors) is 1 */
        result += a->data[y] * b->data[y];
    }
    
    return result;
}

float
le_rbf(LeTensor *a, LeTensor *b, float sigma)
{
    assert(a->shape->num_dimensions == 2);
    assert(b->shape->num_dimensions == 2);

    float result = 0;
    
    /** @todo: Test results against transposed a multiplied by b */
    if (a->shape->sizes[0] != b->shape->sizes[0] || a->shape->sizes[1] != 1 || b->shape->sizes[1] != 1)
        return nanf("");
    
    for (unsigned y = 0; y < a->shape->sizes[0]; y++)
    {
        float sub = a->data[y] - b->data[y];
        result += sub * sub;
    }
    
    return expf(-result / (2.0f * sigma * sigma));
}

void
le_tensor_subtract(LeTensor *a, LeTensor *b)
{
    if (le_shape_equal(a->shape, b->shape))
    {
        unsigned i;
        unsigned elements_count = le_shape_get_elements_count(a->shape);
        
        for (i = 0; i < elements_count; i++)
        {
            a->data[i] -= b->data[i];
        }
    }
}

void
le_matrix_multiply_by_scalar(LeTensor *self, float b)
{
    unsigned i;
    unsigned elements_count = le_shape_get_elements_count(self->shape);
    
    for (i = 0; i < elements_count; i++)
    {
        self->data[i] *= b;
    }
}

void
le_matrix_add_scalar(LeTensor *self, float b)
{
    unsigned i;
    unsigned elements_count = le_shape_get_elements_count(self->shape);
    
    for (i = 0; i < elements_count; i++)
    {
        self->data[i] += b;
    }
}

float
le_matrix_sum(LeTensor *self)
{
    float sum = 0.0;
    unsigned i;
    unsigned elements_count = le_shape_get_elements_count(self->shape);
    
    for (i = 0; i < elements_count; i++)
    {
        sum += self->data[i];
    }
    
    return sum;
}

static float
le_sigmoid(const float a)
{
    return 1.0 / (1.0 + exp(-a));
}

void
le_matrix_apply_sigmoid(LeTensor *self)
{
    unsigned i;
    unsigned elements_count = le_shape_get_elements_count(self->shape);
    
    for (i = 0; i < elements_count; i++)
    {
        self->data[i] = le_sigmoid(self->data[i]);
    }
}

void
le_matrix_apply_greater_than(LeTensor *self, float scalar)
{
    unsigned i;
    unsigned elements_count = le_shape_get_elements_count(self->shape);
    
    for (i = 0; i < elements_count; i++)
    {
        self->data[i] = self->data[i] > scalar ? 1.0f : 0.0f;
    }
}

void
le_matrix_apply_svm_prediction(LeTensor *self)
{
    unsigned i;
    unsigned elements_count = le_shape_get_elements_count(self->shape);
    
    for (i = 0; i < elements_count; i++)
    {
        self->data[i] = self->data[i] > 0.0f ? 1.0f : -1.0f;
    }
}

/** @note: Temporary */
void
le_matrix_print(LeTensor *self, FILE *stream)
{
    if (self->shape->num_dimensions != 2)
    {
        fprintf(stream, "<%dD tensor>\n", self->shape->num_dimensions);
        return;
    }
    
    unsigned x;
    unsigned y;
    fprintf(stream, "[");
    for (y = 0; y < self->shape->sizes[0]; y++)
    {
        for (x = 0; x < self->shape->sizes[1]; x++)
        {
            fprintf(stream, "%1.3f", self->data[y * self->shape->sizes[1] + x]);
            if (x < self->shape->sizes[1] - 1)
            {
                fprintf(stream, " ");
            }
        }
        if (y < self->shape->sizes[0] - 1)
        {
            fprintf(stream, ";\n ");
        }
    }
    fprintf(stream, "]\n");
}

void
le_matrix_free(LeTensor *self)
{
    free(self->shape);
    free(self->data);
    free(self);
}
