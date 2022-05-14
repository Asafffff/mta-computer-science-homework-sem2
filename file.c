#include "file.h"

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
  }

  fclose(outputFile);

  return;
}

/**
 * @brief Returns an array of names of students, with average grade greater than or equal to the given minimum average.
 *
 * @param fileName The name of the file that contains the students.
 * @param minAverage The minimum average.
 * @param resSize The number of students with average grade greater than or equal to the given minimum average.
 * @return char** The array of names of students with average grade greater than or equal to the given minimum average.
 */
// char** findAverageGrade(char* fileName, int minAverage, int* resSize) {
//   int extractedStudentsCount = 0;
//   int studentsAboveAverageCount = 0;
//   STUDENT** extractedStudents = extractStudentsFromFile(fileName, &extractedStudentsCount);

//   char** studentsAboveAverage = (char**)malloc(sizeof(char*) * extractedStudentsCount);

//   for (int i = 0; i < extractedStudentsCount; i++) {
//     if (extractedStudents[i]->average == minAverage) {
//       studentsAboveAverage[studentsAboveAverageCount] = strdup(extractedStudents[i]->name);

//       studentsAboveAverageCount++;
//     }
//   }

//   if (studentsAboveAverageCount == 0) {
//     freeArrayOfStudents(extractedStudents, extractedStudentsCount);
//     free(studentsAboveAverage);

//     *resSize = 0;
//     return NULL;
//   }

//   *resSize = studentsAboveAverageCount;
//   studentsAboveAverage = (char**)realloc(studentsAboveAverage, sizeof(char*) * studentsAboveAverageCount);
//   freeArrayOfStudents(extractedStudents, extractedStudentsCount);

//   return studentsAboveAverage;
// }

int* extractOffsetsFromIndicesFile(char* fileName, int* offsetsArrSize) {
  int currentStudentOffset = 0;
  FILE* indicesFile = fopen(fileName, "rb");
  checkFile(indicesFile);

  int offsetsLogSize = 0;
  int offsetsPhySize = 1;
  int* offsetsArr = (int*)malloc(sizeof(int) * offsetsPhySize);
  checkAllocation(offsetsArr);

  while (fread(&currentStudentOffset, sizeof(int), 1, indicesFile) == 1) {
    if (offsetsLogSize == offsetsPhySize) {
      offsetsPhySize *= 2;
      offsetsArr = (int*)realloc(offsetsArr, sizeof(int) * offsetsPhySize);
      checkAllocation(offsetsArr);
    }

    offsetsArr[offsetsLogSize] = currentStudentOffset;
    offsetsLogSize++;
  }

  fclose(indicesFile);
  offsetsArr = (int*)realloc(offsetsArr, sizeof(int) * offsetsLogSize);

  *offsetsArrSize = offsetsLogSize;
  return offsetsArr;
}

char** findAverageGrade(char* fileName, int minAverage, int* resSize) {
  int offsetArrRequiredIndex, offsetArrRequiredIndexRunner;
  int foundStudentsLogSize = 0, foundStudentsPhySize = 1;
  char** foundStudentsNames = (char**)malloc(sizeof(char*) * foundStudentsPhySize);

  int studentNameLength = 0, studentAverage = 0;
  char* studentName = NULL;

  int offsetsArrSize = 0;
  char* indicesFileName = strdup(fileName);
  strcat(indicesFileName, ".ind");
  int* offsetsArr = extractOffsetsFromIndicesFile(indicesFileName, &offsetsArrSize);
  free(indicesFileName);

  FILE* studentsFile = fopen(fileName, "rb");
  checkFile(studentsFile);

  // Add found student
  offsetArrRequiredIndex = gradesBinarySearchByOffsets(studentsFile, offsetsArr, 0, offsetsArrSize, minAverage);
  if (offsetArrRequiredIndex == NOT_FOUND) {
    *resSize = 0;
    free(offsetsArr);
    fclose(studentsFile);
    return NULL;
  }

  offsetArrRequiredIndexRunner = offsetArrRequiredIndex;

  fseek(studentsFile, offsetsArr[offsetArrRequiredIndex], SEEK_SET);
  fread(&studentNameLength, sizeof(short int), 1, studentsFile);

  studentName = (char*)malloc(sizeof(char) * (studentNameLength + 1));
  checkAllocation(studentName);

  fread(studentName, sizeof(char), studentNameLength, studentsFile);
  studentName[studentNameLength] = '\0';

  foundStudentsNames[foundStudentsLogSize] = strdup(studentName);
  foundStudentsLogSize++;

  // Add students with same grade from left of the required index, if exists
  while (true & offsetArrRequiredIndexRunner > 0) {
    fseek(studentsFile, offsetsArr[offsetArrRequiredIndexRunner - 1], SEEK_SET);
    fread(&studentNameLength, sizeof(short int), 1, studentsFile);
    fseek(studentsFile, studentNameLength, SEEK_CUR);
    fread(&studentAverage, sizeof(int), 1, studentsFile);

    if (studentAverage == minAverage) {
      foundStudentsNames =
          increaseArraySizeIfFull(foundStudentsNames, &foundStudentsLogSize, &foundStudentsPhySize, sizeof(char*));

      fseek(studentsFile, offsetsArr[offsetArrRequiredIndexRunner - 1], SEEK_SET);
      fread(&studentNameLength, sizeof(short int), 1, studentsFile);

      studentName = (char*)realloc(studentName, sizeof(char) * (studentNameLength + 1));
      checkAllocation(studentName);

      fread(studentName, sizeof(char), studentNameLength, studentsFile);
      studentName[studentNameLength] = '\0';

      foundStudentsNames[foundStudentsLogSize] = strdup(studentName);
      foundStudentsLogSize++;
    } else {
      break;
    }
    offsetArrRequiredIndexRunner--;
  }

  // Reset index back to the middle of the array
  offsetArrRequiredIndexRunner = offsetArrRequiredIndex;

  // Add students with same grade from right of the required index, if exists
  while (true & offsetArrRequiredIndexRunner < offsetsArrSize) {
    fseek(studentsFile, offsetsArr[offsetArrRequiredIndexRunner + 1], SEEK_SET);
    fread(&studentNameLength, sizeof(short int), 1, studentsFile);
    fseek(studentsFile, studentNameLength, SEEK_CUR);
    fread(&studentAverage, sizeof(int), 1, studentsFile);

    if (studentAverage == minAverage) {
      foundStudentsNames =
          increaseArraySizeIfFull(foundStudentsNames, &foundStudentsLogSize, &foundStudentsPhySize, sizeof(char*));

      fseek(studentsFile, offsetsArr[offsetArrRequiredIndexRunner - 1], SEEK_SET);
      fread(&studentNameLength, sizeof(short int), 1, studentsFile);

      studentName = (char*)realloc(studentName, sizeof(char) * (studentNameLength + 1));
      checkAllocation(studentName);

      fread(studentName, sizeof(char), studentNameLength, studentsFile);
      studentName[studentNameLength] = '\0';

      foundStudentsNames[foundStudentsLogSize] = strdup(studentName);
      foundStudentsLogSize++;
    } else {
      break;
    }
    offsetArrRequiredIndexRunner++;
  }

  fclose(studentsFile);
  free(studentName);
  free(offsetsArr);
  foundStudentsNames = (char**)realloc(foundStudentsNames, sizeof(char*) * foundStudentsLogSize);
  *resSize = foundStudentsLogSize;
  return foundStudentsNames;
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