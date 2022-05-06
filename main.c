#define _CRT_SECURE_NO_WARNINGS
#include "common.h"
#include "file.h"

void main(int argc, char** argv) {
  if (argc != 2) {
    printf("Invalid number of arguments.\nExiting...");
    exit(1);
  }

  char* studentsBinaryFileName = argv[1];

  int numberOfStudents = 0;
  STUDENT** extractedStudents = extractStudentsFromFile(studentsBinaryFileName, &numberOfStudents);

  mergeSort(extractedStudents, numberOfStudents);
  writeStudentsOffsetsToFile(extractedStudents, numberOfStudents, strcat(studentsBinaryFileName, ".ind"));

  for (int i = 0; i < numberOfStudents; i++) {
    free(extractedStudents[i]->name);
    free(extractedStudents[i]);
  }
  free(extractedStudents);

  return;
}