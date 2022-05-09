#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

//This function will fetch the stream
size_t fetch_contents(char ***contentsptr, size_t *n, FILE *stream);
void nullify_contents(char **contents, size_t begin, size_t end);
void free_contents(char ***contentsptr, size_t n);
void print_contents(char ** contents, size_t n);

int main(int argc, char ** argv) {

  if (argc == 1) {
    char ** contents = NULL;
    size_t n = 0;
    size_t nl = fetch_contents(&contents, &n, stdin);
    sortData(contents, nl);
    print_contents(contents, nl);  
    free_contents(&contents, nl + 1); /* temporary fix one more lines is allocated */
  } else {
    for (int i = 1; i < argc; ++i) {
      char ** contents = NULL;
      size_t n = 0;
      FILE * stream = fopen(argv[i], "r");
      if (!stream) {
	fprintf(stderr, "Fail to open input file");
	return EXIT_FAILURE;
      }
      size_t nl = fetch_contents(&contents, &n, stream);
      if (fclose(stream)) {
	fprintf(stderr, "Fail to close the file");
	free_contents(&contents, nl + 1);
	return EXIT_FAILURE;
      }
      sortData(contents, nl);
      print_contents(contents, nl);
      free_contents(&contents, nl + 1);
    }
  }
  
  return EXIT_SUCCESS;
}

#define BUFSIZE 8

/* ssize_t fetch_lines: return number of lines if successfully fetch
   otherwise return -1. Suppose that contentptr = NULL and *n = 0 */
size_t fetch_contents(char ***contentsptr, size_t *n, FILE *stream) {
  *n = BUFSIZE;
  *contentsptr = malloc(*n * sizeof(**contentsptr));
  nullify_contents(*contentsptr, 0, *n);

  size_t nl = 0; /* serve both number of lines and next available slot */
  size_t sz = 0;
  while (getline(*contentsptr + nl, &sz, stream) > 0) {
    ++nl;
    if (nl == *n) {
      *n *= 2;
      *contentsptr = realloc(*contentsptr, *n * sizeof(**contentsptr));
      nullify_contents(*contentsptr, nl, *n);
    }
  }
  
  return nl;
}


void nullify_contents(char **contents, size_t begin, size_t end) {
  for (size_t i = begin; i < end; ++i)
    contents[i] = NULL;
}

void free_contents(char ***contentsptr, size_t n) {
  for (size_t i = 0; i < n; ++i)
    free((*contentsptr)[i]);
  free(*contentsptr);
}

void print_contents(char **contents, size_t n) {
  for (size_t i = 0; i < n; ++i)
    printf("%s", contents[i]);
}
