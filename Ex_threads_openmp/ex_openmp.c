#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int a[8] = {1,2,3,4,5,6,7,8}, b[8] = {1,2,3,4,5,6,7,8}, c[8];

int m1[3][3] = {
  {1,2,3}, 
  {3,4,3}, 
  {1,2,3}
};

int m2[3][3] = {
  {1,2,3}, 
  {3,4,3},
  {1,2,3}
};

int m3[3][3] = {
  {0,0,0}, 
  {0,0,0},
  {0,0,0}
};

int main (int argc, char *argv[]) 
{
  printf("\n\nInicio da soma de vetores\n");
  #pragma omp parallel for
    for(size_t i = 0; i < 8; i++)
    {
      c[i] = a[i] + b[i];
      printf("%d - %d\n", c[i], omp_get_thread_num());
    }
  printf("\n\nInicio da multiplicacao de matrizes\n");

    #pragma omp parallel for
      for(size_t i = 0; i < 3; i++)
      {
        for(size_t q = 0; q < 3; q++)
        {
          for(size_t j = 0; j < 3; j++)
          {
            m3[i][q] += m1[i][j] * m2[j][q];
          }
        }
      }

      //exibe matriz
      for(size_t u = 0; u < 3; u++)
      {
        for(size_t p = 0; p < 3; p++)
        {
          printf("%d\t", m3[u][p]);
        }
        
          printf("\n");
      }
    
}