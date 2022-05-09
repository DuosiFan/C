#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  size_t inputLength = strlen(inputName);
  size_t outputLength = inputLength + 8;
  char * outputName = malloc(outputLength*sizeof(*outputName));

  for (size_t i = 0; i < inputLength; ++i)
    outputName[i] = inputName[i];
  outputName[inputLength] = '\0';
    
  return strcat(outputName, ".counts");
}
