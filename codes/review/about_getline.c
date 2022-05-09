#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage: ./about_getline inputfile\n");
    return EXIT_FAILURE;
  }
  
  FILE * stream = fopen(argv[1], "r");
  if (!stream) {
    fprintf(stderr, "Fail to open file\n");
    return EXIT_FAILURE;
  }

  char * line = NULL;
  size_t n = 0;
  ssize_t status;
  while ((status = getline(&line, &n, stream)) > 0) {
    printf("%ld: %s", status, line);
  }
  
  if (fclose(stream)) {
    fprintf(stderr, "Fail to close file\n");
    return EXIT_FAILURE;
  }
  
  return 0;
}
