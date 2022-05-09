#include <stddef.h>

size_t maxSeq(int * array, size_t n) {
  size_t maxlength = 0;

  for (int i = 0; i < n; i++) {
    int length = 1;

    for (int j = i+1; j < n; j++)
      if (array[j] > array[j-1])
	length++;
      else
	break;

    maxlength = (length > maxlength) ? length : maxlength;
  }
  
  return maxlength;
}
