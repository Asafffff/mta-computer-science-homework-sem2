#include "file.h"

/**
 * @brief Extracts students from a binary file.
 *
 * @param fileName The name of the file.
 * @param numberOfStudents The number of students in the file.
 * @return STUDENT** The extracted students.
 */
STUDENT** extractStudentsFromFile(char* fileName, int* numberOfStudents) {
  FILE* binaryFile = fopen(fileName, "rb");
  checkFile(binaryFile);
  STUDENT** extractedStudents;

  fread(numberOfStudents, sizeof(short int), 1, binaryFile);

  extractedStudents = (STUDENT**)malloc(sizeof(STUDENT*) * (*numberOfStudents));

  for (int i = 0; i < *numberOfStudents; i++) {
    STUDENT* student = (STUDENT*)malloc(sizeof(STUDENT));
    student->fileOffset = ftell(binaryFile);

    int studentNameLength = 0;
    fread(&studentNameLength, sizeof(short int), 1, binaryFile);

    student->name = (char*)malloc(sizeof(char) * studentNameLength + 1); // +1 for null terminator

    fread(student->name, sizeof(char), studentNameLength, binaryFile);
    student->name[studentNameLength] = '\0';

    fread(&student->average, sizeof(int), 1, binaryFile);

    extractedStudents[i] = student;
  }

  fclose(binaryFile);

  return extractedStudents;
}

/**
 * @brief Returns an array of names of students, with average grade greater than or equal to the given minimum average.
 *
 * @param fileName The name of the file that contains the students.
 * @param minAverage The minimum average.
 * @param resSize The number of students with average grade greater than or equal to the given minimum average.
 * @return char** The array of names of students with average grade greater than or equal to the given minimum average.
 */
char** findAverageGrade(char* fileName, int minAverage, int* resSize) {
  int extractedStudentsCount = 0;
  int studentsAboveAverageCount = 0;
  STUDENT** extractedStudents = extractStudentsFromFile(fileName, &extractedStudentsCount);

  char** studentsAboveAverage = (char**)malloc(sizeof(char*) * extractedStudentsCount);

  for (int i = 0; i < extractedStudentsCount; i++) {
    if (extractedStudents[i]->average == minAverage) {
      studentsAboveAverage[studentsAboveAverageCount] = strdup(extractedStudents[i]->name);

      studentsAboveAverageCount++;
    }
  }

  if (studentsAboveAverageCount == 0) {
    freeArrayOfStudents(extractedStudents, extractedStudentsCount);
    free(studentsAboveAverage);

    *resSize = 0;
    return NULL;
  }

  *resSize = studentsAboveAverageCount;
  studentsAboveAverage = (char**)realloc(studentsAboveAverage, sizeof(char*) * studentsAboveAverageCount);
  freeArrayOfStudents(extractedStudents, extractedStudentsCount);

  return studentsAboveAverage;
}

/**
 * @brief Free the memory allocated for an array of students.
 *
 * @param extractedStudents The array of students.
 * @param extractedStudentsCount The number of students in the array.
 */
void freeArrayOfStudents(STUDENT** extractedStudents, int extractedStudentsCount) {
  for (int i = 0; i < extractedStudentsCount; i++) {
    free(extractedStudents[i]->name);
    free(extractedStudents[i]);
  }
  free(extractedStudents);
}