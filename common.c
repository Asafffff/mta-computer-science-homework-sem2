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

void* scramble(void* arr, int ElemSize, int n, int* indArr) {
  int i;
  BYTE* scrambledArr = (BYTE*)malloc(ElemSize * n);
  checkAllocation(scrambledArr);

  for (i = 0; i < n; i++) {
    int newIndex = indArr[i];
    BYTE* scrambledAddress = scrambledArr + i * ElemSize;
    BYTE* originalAddress = (BYTE*)arr + newIndex * ElemSize;
    memcpy(&scrambledArr[i * ElemSize], &((BYTE*)arr)[newIndex * ElemSize], ElemSize);
  }

  return scrambledArr;
}

int* getIntArr(int* intSize) {
  int arrLogSize = 0;
  int arrPhySize = 1;
  int* intArr = (int*)malloc(arrPhySize * sizeof(int));

  scanf("%d ", intSize);

  for (int i = 0; i < *intSize; i++) {
    intArr = increaseArraySizeIfFull(intArr, &arrLogSize, &arrPhySize, sizeof(int));
    scanf("%d", &intArr[arrLogSize]);
    arrLogSize++;
  }

  intArr = (int*)realloc(intArr, arrLogSize * sizeof(int));
  return intArr;
}

int* scrambleInt(int* intArr, int intSize, int* indArr) {
  int* scrambledArr = (int*)scramble(intArr, sizeof(int), intSize, indArr);

  return scrambledArr;
}

void printIntArr(int* intArr, int intSize) {
  int i;

  for (i = 0; i < intSize; i++) {
    printf("%d ", intArr[i]);
  }
  printf("\n");
}

char** getStringArr(int* stringArrSize) {
  int arrLogSize = 0;
  int arrPhySize = 1;
  char** stringArr = (char**)malloc(arrPhySize * sizeof(char*));

  scanf("%d ", stringArrSize);

  for (int i = 0; i < *stringArrSize; i++) {
    stringArr = increaseArraySizeIfFull(stringArr, &arrLogSize, &arrPhySize, sizeof(char*));

    stringArr[arrLogSize] = (char*)malloc(STRING_MAX_LENGTH * sizeof(char));
    checkAllocation(stringArr[arrLogSize]);

    gets(stringArr[arrLogSize]);

    arrLogSize++;
  }

  stringArr = (char**)realloc(stringArr, arrLogSize * sizeof(char*));
  return stringArr;
}

char** scrambleString(char** stringArr, int stringArrSize, int* indArr) {
  return (char**)scramble(stringArr, sizeof(char*), stringArrSize, indArr);
}

void printStringArr(char** stringArr, int stringArrSize) {
  for (int i = 0; i < stringArrSize; i++) {
    printf("%s\n", stringArr[i]);
  }
}

void freeMemory(int* intArr, int* scrambleIntArr, int intSize, char** stringArr, char** scrambleStringArr,
                int stringSize) {
  free(intArr);
  free(scrambleIntArr);
  for (int i = 0; i < stringSize; i++) {
    free(stringArr[i]);
  }
  free(stringArr);
  free(scrambleStringArr);
}