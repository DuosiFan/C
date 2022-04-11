#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int compare_ints(const void *n1vp, const void *n2vp);
void sort_ints(int * data, size_t n);
void shuffle(int *data, size_t n);
void print_ints(int * data, size_t n);

int main(void)
{
  const size_t n = 1000;
  int data[n];


  for (size_t i = 0; i < n; ++i)
    data[i] = i;
  printf("original array:\n");
  print_ints(data, n);

  shuffle(data, n);
  printf("after shuffling:\n");
  print_ints(data, n);

  sort_ints(data, n);
  printf("after sorting:\n");
  print_ints(data, n);
  return 0;
}

void shuffle(int *data, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    size_t j = i + random()%(n-i);
    int swap = data[i];
    data[i] = data[j];
    data[j] = swap;
  }
}

void print_ints(int *data, size_t n) {
  size_t last_index = n - 1;
  for (size_t i = 0; i < last_index; ++i) {
    printf("%d ", data[i]);
  }
  printf("%d\n", data[last_index]);
}

int compare_ints(const void *n1vp, const void *n2vp) {
  const int * n1ptr = n1vp;
  const int * n2ptr = n2vp;
  return *n1ptr - *n2ptr;
}

void sort_ints(int *data, size_t n) {
  qsort(data, n, sizeof(int), compare_ints);
}

/* funcptr.c ends here */
