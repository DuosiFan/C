#include <stdlib.h>
#include <stdio.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
  /* zero length */
  if (maxSeq(NULL, 0)) {
    printf("NULL test FAILED: expect %ld, get %ld\n", 0L, maxSeq(NULL, 0));
    return EXIT_FAILURE;
  }

  /* length 1 */
  int x0[] = {0};
  if (maxSeq(x0, 1) != 1) {
    printf("length 1 test FAILED: expect %ld, get %ld\n", 1L, maxSeq(x0, 1));
    return EXIT_FAILURE;
  }
  
  /* whole sequence */
  int x1[] = {1, 2, 3, 4, 5, 7};
  if (maxSeq(x1, 7) != 7) {
    printf("whole sequence test FAILED: expect %ld, get %ld\n", 7L, maxSeq(x1, 7));
    return EXIT_FAILURE;
  }

  /* regular overflow */
  int x2[] = {1, 2, 3, -5, 6, -3};
  if (maxSeq(x2, 6) != 3) {
    printf("basic functionality test FAILED: expect %ld, get %ld\n", 3L, maxSeq(x2, 6));
    return EXIT_FAILURE;
  }
  
  /* repeated value */
  int x3[] = {1, 2, 3, 3, -5, -3, -2};
  if (maxSeq(x3, 7) != 3) {
    printf("repeated value test FAILED: expect %ld, get %ld\n", 3L, maxSeq(x3, 7));
    return EXIT_FAILURE;
  }

  /* repeated value 2 */
  int x4[] = {2, 2, 3, 3};
  if (maxSeq(x4, 4) != 2) {
    printf("repeated value 2 test FAILED: expect %ld, get %ld\n", 4L, maxSeq(x4, 4));
    return EXIT_FAILURE;
  }

  printf("All tests passed!\n");
  return EXIT_SUCCESS;
}
