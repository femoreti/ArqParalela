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

void *SomaVetor(void *arg)
{
  int tID = *(int*)arg;
  tID += 1;

  int initialIndex = 2 * (tID - 1);

  for(size_t i = initialIndex; i < initialIndex + 2; i++)
  {
    c[i] = a[i] + b[i];

    printf("%d\n", c[i]);
  }

  return NULL;
}

void *MultiVetor(void *arg)
{
  int tID = *(int*)arg;

  int initialIndex = (tID);

  for(size_t q = 0; q < 3; q++)
  {
    for(size_t j = 0; j < 3; j++)
    {
      m3[initialIndex][q] += m1[initialIndex][j] * m2[j][q];
    }
  }

  //exibe matriz
  for(size_t p = 0; p < 3; p++)
  {
    printf("%d\t", m3[initialIndex][p]);
  }
  printf("\n");
}

int main (int argc, char *argv[]) 
{
  printf("Soma matrizes\n");

  pthread_t threadID[4];
  for(size_t i = 0; i < 4; i++)
  {
    pthread_create(&threadID[i], NULL, SomaVetor,(void *)&i);
    pthread_join(threadID[i], NULL);
  }

  printf("\n");
  printf("Multiplica matrizes\n");
  
  pthread_t threadIDM[3];
  for(size_t i = 0; i < 3; i++)
  {
    pthread_create(&threadIDM[i], NULL, MultiVetor,(void *)&i);
    pthread_join(threadIDM[i], NULL);
  }
}