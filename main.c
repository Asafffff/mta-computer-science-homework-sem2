#define _CRT_SECURE_NO_WARNINGS
#include "common.h"
#include "file.h"

void main(int argc, char** argv) {
  if (argc != 3) {
    printf("Invalid number of arguments.\nExiting...");
    exit(1);
  }

  char* binaryFileName = argv[1];
  int numberOfStrings = atoi(argv[2]);

  char** extractedStrings = readBinaryFileLowerChars(binaryFileName, numberOfStrings);
  sortLexicographically(extractedStrings, numberOfStrings);

  strcat(binaryFileName, ".txt");
  writeOutputToTxtFile(extractedStrings, numberOfStrings, binaryFileName);

  for (int i = 0; i < numberOfStrings; i++) {
    free(extractedStrings[i]);
    extractedStrings[i] = NULL;
  }
  free(extractedStrings);

  extractedStrings = NULL;

  return;
}