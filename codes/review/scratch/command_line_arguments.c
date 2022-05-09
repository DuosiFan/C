#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  printf("I have %d command line arguments:\n", argc);

  for (size_t i = 0; i < argc; ++i)
    printf("%s\n", argv[i]);
  
  return EXIT_SUCCESS;
}
