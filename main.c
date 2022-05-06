#define _CRT_SECURE_NO_WARNINGS
#include "common.h"
#include "file.h"

void main(int argc, char* argv[]) {
  char** records;
  int resSize;

  records = findAverageGrade(argv[1], 85, &resSize);
  printNames(records, resSize);
  // free records!
}

void printNames(char** records, int size) {

  int i;

  printf("The students names are:\n");

  for (i = 0; i < size; i++)
    printf("%s\n", records[i]);
}