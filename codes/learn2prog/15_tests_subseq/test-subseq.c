#include <stdlib.h>
#include <stdio.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
  /* zero length */
  if (maxSeq(NULL, 0)) return EXIT_FAILURE;

  /* length 1 */
  int x0[] = {0};
  if (maxSeq(x0, 1) != 1) return EXIT_FAILURE;
  
  /* whole sequence */
  int x1[] = {1, 2, 3, 4, 5, 7};
  if (maxSeq(x1, 7) != 7) return EXIT_FAILURE;

  /* regular overflow */
  int x2[] = {1, 2, 3, -5, 6, -3};
  if (maxSeq(x2, 6) != 3) return EXIT_FAILURE;
  
  /* repeated value */
  int x3[] = {1, 2, 3, 3, -5, -3, -2};
  if (maxSeq(x3, 7) != 3) return EXIT_FAILURE;

  /* repeated value 2 */
  int x4[] = {2, 2, 3, 3};
  if (maxSeq(x4, 4) != 2) return EXIT_FAILURE;
  
  return EXIT_SUCCESS;
}