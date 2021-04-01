#include <time.h>
#include <math.h>
#include <stdlib.h>

#include "procedures.h"

static int count = 0;

static float *generate(int n, int m)
{
    float *pmatrix;
    pmatrix = (float*) malloc(sizeof(float) * n * m);
    if (pmatrix == 0)
    {
        printf("Bad alloc");
        abort();
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            pmatrix[i * m + j] = 100 / ((float) (i + j));
    return pmatrix;
}

static void destroy(float *pmatrix)
{
    free(pmatrix);
}

void cpu_bound_function(int size)
{
    // Matrix Multiplication
    float *A = generate(size, size),
          *B = generate(size, size),
          *C = generate(size, size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            C[i * size + j] = 0.0f;
    // do multi
    for (int k = 0; k < size; ++k)
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                C[i * size + j] += A[i * size + k] + B[k * size + j];
    count++;
    printf("Call cpu bound function for the %d th time.\n", count);
    destroy(A);
    destroy(B);
    destroy(C);
}
