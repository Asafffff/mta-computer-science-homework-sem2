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

void copyArr(STUDENT* src[], STUDENT* dest[], int size) {
  int i;

  for (i = 0; i < size; i++) {
    dest[i] = src[i];
  }

  return;
}

void merge(STUDENT* arr1[], int size1, STUDENT* arr2[], int size2, STUDENT* tmpArr[]) {
  int index1, index2, writeIndex;
  index1 = index2 = writeIndex = 0;

  while (index1 < size1 && index2 < size2) {
    if (arr1[index1]->average <= arr2[index2]->average) {
      tmpArr[writeIndex] = arr1[index1];
      index1++;
    } else {
      tmpArr[writeIndex] = arr2[index2];
      index2++;
    }
    writeIndex++;
  }

  while (index1 < size1) {
    tmpArr[writeIndex] = arr1[index1];
    index1++;
    writeIndex++;
  }

  while (index2 < size2) {
    tmpArr[writeIndex] = arr2[index2];
    index2++;
    writeIndex++;
  }
}

void mergeSort(STUDENT** arr, int size) {
  int halfSize = size / 2;
  STUDENT** tmpArr;

  if (size < 2) {
    return;
  }

  mergeSort(arr, halfSize);
  mergeSort(arr + halfSize, size - halfSize);

  tmpArr = (STUDENT**)malloc(size * sizeof(STUDENT*));
  checkAllocation(tmpArr);

  merge(arr, halfSize, arr + halfSize, size - halfSize, tmpArr);
  copyArr(tmpArr, arr, size);
  free(tmpArr);
}
