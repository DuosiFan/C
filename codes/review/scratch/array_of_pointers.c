#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define N 100
#define LOC 4

int main(void)
{
  /* array of data */
  int* data = NULL;
  /* array of pointers */
  int** ptrs = NULL;

  data = (int*) malloc(N*sizeof(int));
  ptrs = (int**) malloc(N*sizeof(int*));

  for (size_t i = 0; i < N; ++i)
    *(data + i) = i;

  /* create a pointer to data[4] */
  int* ptr = data + LOC;
  printf("ptr points at %p with value %d\n", ptr, *ptr);


  /* associate data and ptrs */
  for (size_t i = 0; i < N; ++i)
    *(ptrs + i) = data + i;

  
  /* shuffle the data by pointers */
  for (size_t i = 0; i < N; ++i) {
    size_t j = i + random()%(N - i);

    int* swap = *(ptrs + i);
    *(ptrs + i) = *(ptrs + j);
    *(ptrs + j) = swap;
  }
    
  printf("Now, ptr points at %p with value %d\n", ptr, *ptr);
  
  
  free(ptrs);
  free(data);
  return 0;
}
