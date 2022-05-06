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
 * @brief Writes the offsets of the students in the file.
 *
 * @param students The students to write.
 * @param numberOfStudents The number of students.
 * @param fileName The name of the file.
 */
void writeStudentsOffsetsToFile(STUDENT** students, int numberOfStudents, char* fileName) {
  FILE* outputFile = fopen(fileName, "wb");
  checkFile(outputFile);

  for (int i = 0; i < numberOfStudents; i++) {
    fprintf(outputFile, "%ld", students[i]->fileOffset);

    if (i != numberOfStudents - 1) {
      fprintf(outputFile, "\n");
    }
  }

  fclose(outputFile);

  return;
}