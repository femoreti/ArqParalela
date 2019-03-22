#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define N 8
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

int main(void)
{
    int A[N] = {1,2,3,4};
    int B[N*2] = {0,0,0,0,0,0,0,0};

    #pragma omp parallel for
    for(size_t i = 0; i < N; i++)
    {
        B[N+i] = A[i];
    }

    for(size_t i = 0; i < N*2; i++)
    {
        printf("%d ", B[i]);
    }

    for(size_t j = log2(N) - 1; j > 0; j--)
    {
        int x = pow(2,j+1) - 1;

        #pragma omp parallel for
        for(size_t q = pow(2, j) - 1; q <= x; q++)
        {
           B[q] = max(B[2 * q], B[2 * q + 1]);
        }
    }

    printf("\n");

    for(size_t i = 0; i < N*2; i++)
    {
        printf("%d ", B[i]);
    }

    printf("\n\n%d\n", B[1]);

    return 0;
}