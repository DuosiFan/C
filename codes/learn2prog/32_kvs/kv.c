#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

#define BUFSIZE 8

static kvpair_t * split_line(const char * line);

kvarray_t * readKVs(const char * fname) {
  FILE * stream = fopen(fname, "r");
  if (!stream) {
    fprintf(stderr, "Fail to open file\n");
    return NULL;
  }
  
  kvarray_t * pairs = malloc(sizeof(*pairs));
  pairs->num_pairs = 0;
  pairs->num_ptrs = BUFSIZE;
  pairs->pairs = malloc(pairs->num_ptrs*sizeof(*(pairs->pairs)));

  char * line = NULL;
  size_t n = 0;
  while (getline(&line, &n, stream) > 0) {
    (pairs->pairs)[pairs->num_pairs++] = split_line(line);
    if (pairs->num_pairs >= pairs->num_ptrs) {
      pairs->num_ptrs *= 2;
      pairs->pairs = realloc(pairs->pairs, pairs->num_ptrs*sizeof(*(pairs->pairs)));
    }
  }

  free(line);
  if (fclose(stream)) {
    fprintf(stderr, "Fail to close file\n");
  }
  
  return pairs;
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->num_pairs; ++i) {
    free((pairs->pairs)[i]->key);
    free((pairs->pairs)[i]->value);
    free((pairs->pairs)[i]);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->num_pairs; ++i) {
    kvpair_t * pair = pairs->pairs[i];
    printf("key = '%s' value = '%s'\n", pair->key, pair->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < pairs->num_pairs; ++i)
    if (!strcmp(key, (pairs->pairs)[i]->key))
      return (pairs->pairs)[i]->value;
  
  return NULL;
}

/* file scope functions */

/* assumption:
   1. line is null terminated string
   2. A newline appears before the null terminator
   return:
   1. If '=' is found, return a pointer to a key-value pair
   with allocated storage as a side effect
   2. If '=' is not found, return NULL with no side effect */
static kvpair_t *split_line(const char *line) {
  char * delimiter = strchr(line, '=');
  if (!delimiter) {
    return NULL;
  }

  size_t length_line = strlen(line);
  assert(line[length_line-1] == '\n');
  int length_key = delimiter - line;
  int length_value = strlen(line) - length_key - 2; /* '=' and '\n' */

  kvpair_t * pair = malloc(sizeof(*pair));
  pair->key = malloc((length_key+1)*sizeof(*(pair->key)));
  pair->value = malloc((length_value+1)*sizeof(*(pair->value)));

  for (size_t i = 0; i < length_key; ++i)
    (pair->key)[i] = line[i];
  (pair->key)[length_key] = '\0';

  for (size_t i = length_key + 1; i < length_line - 1; ++i)
    (pair->value)[i-length_key-1] = line[i];
  (pair->value)[length_value] = '\0';
  
  return pair;
}
