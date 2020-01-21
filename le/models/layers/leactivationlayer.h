/* Copyright (c) Kyrylo Polezhaiev and contributors. All rights reserved.
   Released under the MIT license. See LICENSE file in the project root for full license information. */

#ifndef __LEACTIVATIONLAYER_H__
#define __LEACTIVATIONLAYER_H__

#include "lelayer.h"

typedef enum LeActivation
{
    LE_ACTIVATION_LINEAR,
    LE_ACTIVATION_TANH,
    LE_ACTIVATION_SOFTMAX
} LeActivation;

typedef struct LeActivationLayer
{
    LeLayer parent;
    
    LeActivation activation;
} LeActivationLayer;

#define LE_ACTIVATION_LAYER(a) ((LeActivationLayer *)(a))

LeActivationLayer * le_activation_layer_new (const char   *name,
                                             LeActivation  activation);

#endif
