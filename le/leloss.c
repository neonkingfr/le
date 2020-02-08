/* Copyright (c) Kyrylo Polezhaiev and contributors. All rights reserved.
   Released under the MIT license. See LICENSE file in the project root for full license information. */

#include "leloss.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include "letensor-imp.h"

float
le_logistic_loss(LeTensor *h, LeTensor *y)
{
    assert(h->shape->num_dimensions == 2);
    assert(y->shape->num_dimensions == 2);
    assert(h->shape->sizes[1] == y->shape->sizes[1]);
    
    float result = 0.0f;
    unsigned i;
    
    unsigned elements_count = le_shape_get_elements_count(h->shape);
    for (i = 0; i < elements_count; i++)
    {
        float yi = le_tensor_f32_at(y, i);
        float hi = le_tensor_f32_at(h, i);
        result -= yi * log(hi) + (1.0f - yi) * log(1.0f - hi);
    }
    
    return result / elements_count;
}

float
le_cross_entropy_loss(LeTensor *h, LeTensor *y)
{
    assert(h->shape->num_dimensions == 2);
    assert(y->shape->num_dimensions == 2);
    assert(h->shape->sizes[1] == y->shape->sizes[1]);
    
    unsigned num_classes = y->shape->sizes[0];
    unsigned num_examples = y->shape->sizes[1];
    
    float cost = 0.0f;
    for (unsigned i = 0; i < num_examples; i++)
    {
        float loss = 0.0f;
        for (unsigned j = 0; j < num_classes; j++)
        {
            float y_ji = le_matrix_at(y, j, i);
            float y_hji = le_matrix_at(h, j, i);
            loss -= y_ji * logf(y_hji);
        }
        cost += loss;
    }
    
    return cost / num_examples;
}

float
le_one_hot_misclassification(LeTensor *h, LeTensor *y)
{
    assert(h->shape->num_dimensions == 2);
    assert(y->shape->num_dimensions == 2);
    assert(h->shape->sizes[1] == y->shape->sizes[1]);
    
    unsigned i, j;
    
    unsigned classes_count = y->shape->sizes[0];
    unsigned examples_count = y->shape->sizes[1];
    unsigned misclassified_count = 0;
    
    for (i = 0; i < examples_count; i++)
    {
        int predicted_class = -2;
        float predicted_class_probability = 0.0f;
        int labeled_class = -1;
        float labeled_class_probability = 0.0f;
        for (j = 0; j < classes_count; j++)
        {
            float predicted_probability = le_matrix_at(h, j, i);
            if (predicted_probability > predicted_class_probability)
            {
                predicted_class_probability = predicted_probability;
                predicted_class = j;
            }
            float labeled_probability = le_matrix_at(y, j, i);
            if (labeled_probability > labeled_class_probability)
            {
                labeled_class_probability = labeled_probability;
                labeled_class = j;
            }
        }
        if (predicted_class != labeled_class)
        {
            misclassified_count++;
        }
    }
    
    return ((float)misclassified_count) / ((float)examples_count);
}

void
le_apply_loss_derivative(LeTensor *h, LeTensor *y)
{
    assert(h->shape->num_dimensions == 2);
    assert(y->shape->num_dimensions == 2);
    assert(le_shape_equal(h->shape, y->shape));

    unsigned i;
    
    unsigned elements_count = le_shape_get_elements_count(h->shape);
    for (i = 0; i < elements_count; i++)
    {
        float yi = le_tensor_f32_at(y, i);
        float hi = le_tensor_f32_at(h, i);
        float dJ_dh = (hi - yi) / (hi * (1 - hi));
        le_tensor_f32_set(h, i, dJ_dh);
    }
}
