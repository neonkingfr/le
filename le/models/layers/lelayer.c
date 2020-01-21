/* Copyright (c) Kyrylo Polezhaiev and contributors. All rights reserved.
   Released under the MIT license. See LICENSE file in the project root for full license information. */

#include "lelayer.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <le/lematrix.h>

void
le_layer_construct(LeLayer *layer, const char *name)
{
    assert(layer);
    
    layer->parameters = NULL;
    layer->name = strdup(name);
}

LeTensor *
le_layer_forward_prop(LeLayer *layer, LeTensor *input)
{
    assert(layer);
    LeLayerClass *klass = (LeLayerClass *)LE_OBJECT_GET_CLASS(layer);
    assert(klass);
    assert(klass->forward_prop);

    return klass->forward_prop(layer, input);
}

LeList *
le_layer_get_parameters(LeLayer *self)
{
    assert(self);
    
    return self->parameters;
}

void
le_layer_append_parameter(LeLayer *self, LeTensor *parameter)
{
    assert(self);
    assert(parameter);
    
    self->parameters = le_list_append(self->parameters, parameter);
}

LeList *
le_layer_get_gradients(LeLayer *self)
{
    assert(self);
    
    return NULL;
}
