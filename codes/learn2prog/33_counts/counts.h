#ifndef __COUNTS_H__
#define __COUNTS_H__
struct _one_count_t {
  char * item;
  size_t n;  
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  one_count_t ** items;
  size_t num_items;
  size_t num_unknown;
  size_t size;
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif
