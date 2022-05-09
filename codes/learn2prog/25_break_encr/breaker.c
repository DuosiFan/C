#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stddef.h>

void count_frequency(FILE *f, int *counts);
size_t get_max_index(int * data, int n);

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage: ./breaker input\n");
    return EXIT_FAILURE;
  }
  
  FILE * f = fopen(argv[1], "r");
  if (!f) {
    fprintf(stderr, "Cannot open the input file\n");
    return EXIT_FAILURE;
  }
  
  int counts[26] = {0};
  count_frequency(f, counts);
  if (fclose(f)) {
    perror("Fail to close the input file\n");
    return EXIT_FAILURE;
  }

  size_t max_index = get_max_index(counts, 26);
  int key;
  if (max_index >= 'e' - 'a')
    key = max_index + 'a' - 'e';
  else
    key = max_index + 'a' + 26 - 'e';

  printf("%d\n", key);
  
  return EXIT_SUCCESS;
}

void count_frequency(FILE *f, int *counts) {
  assert(f);

  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      ++counts[c - 'a'];
    }
  }
}


/* For repeated counts, the smaller index will be returned */
size_t get_max_index(int *data, int n) {
  int max_element = -1;
  size_t max_index = 0;
  for (size_t i = 0; i < n; ++i)
    if (data[i] > max_element) {
      max_element = data[i];
      max_index = i;
    }
  assert(max_element != -1);
  return max_index;
}
