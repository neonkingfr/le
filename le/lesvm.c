/* Copyright (c) Kyrylo Polezhaiev and contributors. All rights reserved.
   Released under the MIT license. See LICENSE file in the project root for full license information. */

#include "lesvm.h"
#include <stdlib.h>
#include "lemodel.h"

struct LeSVM
{
    LeModel   parent;
    LeMatrix *weights;
    float     bias;
    float     c;
    LeKernel  kernel;
};

typedef struct LeSVMClass
{
    LeModelClass parent;
} LeSVMClass;

LeSVMClass le_svm_class;

LeMatrix * le_svm_predict(LeSVM *self, LeMatrix *x);

void
le_svm_class_ensure_init(void)
{
    static int le_svm_class_initialized = 0;
    
    if (!le_svm_class_initialized)
    {
        le_svm_class.parent.predict =
        (LeMatrix *(*)(LeModel *, LeMatrix *))le_svm_predict;
        le_svm_class_initialized = 1;
    }
}

void
le_svm_construct(LeSVM *self)
{
    le_model_construct((LeModel *)self);
    le_svm_class_ensure_init();
    ((LeObject *)self)->klass = (LeClass *)&le_svm_class;
    self->weights = NULL;
    self->c = 0.0;
    self->kernel = LE_KERNEL_LINEAR;
}

LeSVM *
le_svm_new(void)
{
    LeSVM *self = malloc(sizeof(struct LeSVM));
    le_svm_construct(self);
    return self;
}

void
le_svm_train(LeSVM *self, LeMatrix *x_train, LeMatrix *y_train, LeKernel kernel)
{
    /// @todo: Sequential Minimal Optimization here
}

LeMatrix *
le_svm_predict(LeSVM *self, LeMatrix *x)
{
    if (self == NULL)
        return NULL;
    if (self->weights == NULL)
        return NULL;
    LeMatrix *wt = le_matrix_new_transpose(self->weights);
    LeMatrix *a = le_matrix_new_product(wt, x);
    le_matrix_free(wt);
    le_matrix_add_scalar(a, self->bias);
    le_matrix_apply_greater_than(a, 0);
    return a;
}

void
le_svm_free(LeSVM *self)
{
    free(self);
}
