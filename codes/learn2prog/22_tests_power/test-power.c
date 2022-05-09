#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned power(unsigned x, unsigned y);
int run_check(unsigned x, unsigned y, unsigned expected);

int main(void)
{
  /* test suite */
  unsigned x[] = {2, 10, 0, UINT_MAX};
  unsigned y[] = {3, 4, 0, 1};
  unsigned expected[] = {8, 10000, 1, UINT_MAX};

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
