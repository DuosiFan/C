#include <stddef.h>
#include <stdio.h>

int main(void)
{
  int m[4][3];
  for (size_t i = 0; i < 4; i++)
    for (size_t j = 0; j < 3; j++)
      m[i][j] = i + j;

  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 3; j++)
      printf("%d ", m[i][j]);
    printf("\n");
  }

  /* array of pointers */
  int row0[3] = {0};
  int garbage = 1;
  int row1[3] = {garbage, garbage, garbage};

  int *matrix23[2] = {row0, row1};

  for (size_t i = 0; i < 2; i++) {
    for (size_t j = 0; j < 3; j++)
      printf("%d ", *(*(matrix23 + i) + j));
    printf("\n");
  }

  return 0;
}
