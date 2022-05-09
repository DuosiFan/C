#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define N 10
#define BUFSIZE 20
#define SUCCESS 1
#define FAIL 0

int fetch_matrix(FILE * stream, char matrix[N][N]);
void rotate(char matrix[N][N]);

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage: ./rotateMatrix input.txt\n");
    return EXIT_FAILURE;
  }

  FILE * stream = fopen(argv[1], "r");
  if (!stream) {
    fprintf(stderr, "Cannot open the input file\n");
    return EXIT_FAILURE;
  }

  /* read the data */
  char matrix[N][N];
  int fetch_status = fetch_matrix(stream, matrix);

  if (fetch_status == FAIL) {
    fprintf(stderr, "Invalid format\n");
    if (fclose(stream))
      fprintf(stderr, "Cannot close the input file\n");
    return EXIT_FAILURE;
  } else {
    if (fclose(stream)) {
      fprintf(stderr, "Cannot close the input file\n");
      return EXIT_FAILURE;
    }
  }

  /* perform rotate */
  rotate(matrix);

  /* write output */
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      putchar(matrix[i][j]);
    }
    putchar('\n');
  }

  return 0;
}


int fetch_matrix(FILE * stream, char matrix[N][N]) {
  char buffer[BUFSIZE];
  int nlines = 0;

  for (size_t i = 0; i < N; ++i) {
    char * s = fgets(buffer, BUFSIZE, stream);
    if (!s || strlen(buffer) != N + 1 || !strchr(buffer, '\n'))
      return FAIL;

    /* parse buffer to the matrix */
    for (size_t j = 0; j < N; ++j) {
      /* if (!isprint(buffer[j])) { */
      /* 	return FAIL; */
      /* } */
      matrix[i][j] = buffer[j];
    }
    ++nlines;
    if (nlines > N)
      return FAIL;
  }

  char * s = fgets(buffer, BUFSIZE, stream);
  if (s)
    return FAIL;
  
  assert(nlines == N);

  return SUCCESS;
}

void rotate(char matrix[N][N]) {
  char matrixc[10][10]; /* local copy */

  for (size_t i = 0; i < N; ++i)
    for (size_t j = 0; j < N; ++j)
      matrixc[i][j] = matrix[N-1-j][i];

  /* copy back */
  for (size_t i = 0; i < N; ++i)
    for (size_t j = 0; j < N; ++j)
      matrix[i][j] = matrixc[i][j];
}
