#include "letests-matrices.h"
#include <le/le.h>

int
le_test_ensure_matrix_size(LeMatrix *a, unsigned height, unsigned width)
{
    if (a == NULL)
    {
        printf("NULL pointer given");
        return 1;
    }
    
    if (le_matrix_get_width(a) != width)
    {
        printf("Wrong matrix width.\n");
        return 1;
    }
    
    if (le_matrix_get_height(a) != height)
    {
        printf("Wrong matrix height.\n");
        return 1;
    }
    
    return 0;
}

#define MAX_DIMENSION 4

int
le_test_matrices()
{
    unsigned width;
    unsigned height;
    unsigned second_width;
    
    LeMatrix *a;
    LeMatrix *b;
    LeMatrix *c;
    
    for (height = 1; height < MAX_DIMENSION; height++)
    {
        a = le_matrix_new_identity(height);
        if (le_test_ensure_matrix_size(a, height, height) != 0)
        {
            printf("Problem occured when testing sizes of identity matrix.\n");
            return 0;
        }
        le_matrix_free(a);
        
        for (width = 1; width < MAX_DIMENSION; width++)
        {
            a = le_matrix_new_zeros(height, width);
            if (le_test_ensure_matrix_size(a, height, width) != 0)
            {
                printf("Problem occured when testing sizes of zeros matrix.\n");
                return 0;
            }
            le_matrix_free(a);
            
            a = le_matrix_new_rand(height, width);
            if (le_test_ensure_matrix_size(a, height, width) != 0)
            {
                printf("Problem occured when testing sizes of random matrix.\n");
                return 0;
            }
            
            for (second_width = 1; second_width < MAX_DIMENSION; second_width++)
            {
                b = le_matrix_new_rand(width, second_width);
                c = le_matrix_new_product(a, b);
                if (le_test_ensure_matrix_size(c, height, second_width) != 0)
                {
                    printf("Problem occured when testing sizes of matrix product.\n");
                    return 0;
                }
                le_matrix_free(c);
                le_matrix_free(b);
            }
            
            le_matrix_free(a);
        }
    }
    return 0;
}
