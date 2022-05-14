#include "common.h"

void checkAllocation(void* ptr) {
  if (ptr == NULL) {
    exit(1);
  }
}

void checkFile(FILE* file) {
  if (file == NULL) {
    printf("Could not open file.\nExiting...");
    exit(1);
  }
}

/**
 * @brief Increases the size of the array, if it is full
 *
 * @param arr The array to be resized
 * @param logSize The logical size of the array
 * @param phySize The physical size of the array
 * @return void* The resized array, before casting to the original type
 */
void* increaseArraySizeIfFull(void* arr, int* logSize, int* phySize, unsigned long sizeOfType) {
  if (*logSize == *phySize) {
    (*phySize) *= 2;
    arr = realloc(arr, (*phySize) * sizeOfType);
    checkAllocation(arr);
  }

  return arr;
}

int gradesBinarySearchByOffsets(FILE* studentsFile, int arr[], int leftInd, int rightInd, int wantedGrade) {
  int currentStudentNameLength = 0;
  int currentStudentAverage = 0;

  int mid = (leftInd + rightInd) / 2;

  if (leftInd <= rightInd) {
    fseek(studentsFile, arr[mid], SEEK_SET);
    fread(&currentStudentNameLength, sizeof(short int), 1, studentsFile);
    fseek(studentsFile, currentStudentNameLength, SEEK_CUR);
    fread(&currentStudentAverage, sizeof(int), 1, studentsFile);

    if (currentStudentAverage == wantedGrade) {
      int indexOfEarlierOccourence = gradesBinarySearchByOffsets(studentsFile, arr, leftInd, mid - 1, wantedGrade);
      return indexOfEarlierOccourence != NOT_FOUND ? indexOfEarlierOccourence : mid;
    }

    if (wantedGrade < currentStudentAverage) {
      return gradesBinarySearchByOffsets(studentsFile, arr, leftInd, mid - 1, wantedGrade);
    } else {
      return gradesBinarySearchByOffsets(studentsFile, arr, mid + 1, rightInd, wantedGrade);
    }
  }

  return NOT_FOUND;
}