#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
#define BUFSIZE 8

static int contains(counts_t * c, const char * name);

counts_t * createCounts(void) {
  counts_t * c = malloc(sizeof(*c));
  c->num_items = 0;
  c->num_unknown = 0;
  c->size = BUFSIZE;
  c->items = malloc(c->size*sizeof(*c->items));
  return c;
}
void addCount(counts_t * c, const char * name) {
  if (!name) {
    ++c->num_unknown;
    return;
  }

  int loc = contains(c, name);
  if (loc != -1) {
    ++(c->items)[loc]->n;
  } else {
    one_count_t * item = malloc(sizeof(*item));
    item->item = malloc((strlen(name)+1)*sizeof(*item->item));
    item->n = 1;
    strcpy(item->item, name);
    (c->items)[c->num_items++] = item;
    if (c->num_items >= c->size) {
      c->size *= 2;
      c->items = realloc(c->items, c->size*sizeof(*(c->items)));
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  for (size_t i = 0; i < c->num_items; ++i)
    fprintf(outFile, "%s: %zu\n", (c->items)[i]->item, (c->items)[i]->n);

  if (c->num_unknown)
    fprintf(outFile, "<unknown> : %zu\n", c->num_unknown);
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->num_items; ++i) {
    free((c->items)[i]->item);
    free((c->items)[i]);
  }
  free(c->items);
  free(c);
}

/* assume both strings are null-terminated */
int contains(counts_t *c, const char *name) {
  for (size_t i = 0; i < c->num_items; ++i) {
    if (!strcmp(name, (c->items)[i]->item))
      return i;
  }
  return -1;
}
