#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE * f = fopen("input.txt", "r");

  if (f == NULL) {
    printf("input.txt does not exist\n");
    return EXIT_FAILURE;
  }
  
  int c;
  while ((c = fgetc(f)) != EOF) {
    putchar(c);
  }
  
  return EXIT_SUCCESS;
}
