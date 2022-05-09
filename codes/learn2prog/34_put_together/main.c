#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE * stream = fopen(filename, "r");
  if (!stream) {
    fprintf(stderr, "Fail to open file\n");
    return NULL;
  }
  
  counts_t * c = createCounts();
  char * line = NULL;
  size_t n = 0;
  while (getline(&line, &n, stream) > 0) {
    size_t length_line = strlen(line);
    assert(line[length_line-1] == '\n');
    line[length_line-1] = '\0';
    addCount(c, lookupValue(kvPairs, line));
  }
  free(line);

  if (fclose(stream)) {
    fprintf(stderr, "Fail to close file\n");
  }
  
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 3) {
    fprintf(stderr, "Usage: ./count_values <kv.txt> <list.txt> ...\n");
    return EXIT_FAILURE;
  }

  kvarray_t * kvPairs = readKVs(argv[1]);
  if (!kvPairs) {
    fprintf(stderr, "Fail to read key/value pairs\n");
    return EXIT_FAILURE;
  }
  
  //count from 2 to argc (call the number you count i)
  for (size_t i = 2; i < argc; ++i) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kvPairs);
    
    //compute the output file name from argv[i] (call this outName)
    char * output = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE *out_stream = fopen(output, "w");
    if (!out_stream) {
      fprintf(stderr, "Fail to open the output file\n");
      free(output);
      freeCounts(c);
      return EXIT_FAILURE;
    }

    //print the counts from c into the FILE f
    printCounts(c, out_stream);
    //close f
    if (fclose(out_stream)) {
      fprintf(stderr, "Fail to close the output file\n");
      free(output);
      freeCounts(c);
      return EXIT_FAILURE;      
    }
    //free the memory for outName and c
    free(output);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kvPairs);
  
  return EXIT_SUCCESS;
}
