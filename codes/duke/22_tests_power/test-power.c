#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);
int run_check(unsigned x, unsigned y, unsigned expected);

int main(void)
{
  /* test suite */
  unsigned x[] = {0, 2, 1};
  unsigned y[] = {0, 3, 0};
  unsigned expected[] = {1, 8, 1};

  /* check test suite dim */
  size_t n = sizeof(x)/sizeof(x[0]);
  if (sizeof(y)/sizeof(y[0]) != n || sizeof(expected)/sizeof(expected[0]) != n)
    exit(EXIT_FAILURE);

  for (size_t i = 0; i < n; i++)
    if (!run_check(x[i], y[i], expected[i]))
      exit(EXIT_FAILURE);
  
  return EXIT_SUCCESS;
}

int run_check(unsigned x, unsigned y, unsigned expected) {
  return power(x, y) == expected;
}
