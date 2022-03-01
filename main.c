#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** pointerSort(int* arr, unsigned int size, int ascend_flag);
void printPointers(int** arr, unsigned int size);
void copyArr(int src[], int dest[], int size);
void mergeAscending(int arr1[], int size1, int arr2[], int size2, int tmpArr[]);
void mergeDescending(int arr1[], int size1, int arr2[], int size2, int tmpArr[]);
void mergeSort(int arr[], int size, bool isAscending);

#define SIZE 100

void main()

{

  unsigned int size, i;

  int arr[SIZE];

  int** pointers;

  int ascend_flag;

  printf("Please enter the number of items:\n");

  scanf("%u", &size);

  for (i = 0; i < size; i++)

    scanf("%d", &arr[i]);

  scanf("%d", &ascend_flag);

  pointers = pointerSort(arr, size, ascend_flag);

  printf("The sorted array:\n"); // Print the sorted array

  printPointers(pointers, size);

  free(pointers);
}

void copyArr(int src[], int dest[], int size) {
  int i;

  for (i = 0; i < size; i++) {
    dest[i] = src[i];
  }

  return;
}

void mergeAscending(int arr1[], int size1, int arr2[], int size2, int tmpArr[]) {
  int index1, index2, writeIndex;
  index1 = index2 = writeIndex = 0;

  while (index1 < size1 && index2 < size2) {
    if (arr1[index1] <= arr2[index2]) {
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

void mergeDescending(int arr1[], int size1, int arr2[], int size2, int tmpArr[]) {
  int index1, index2, writeIndex;
  index1 = index2 = writeIndex = 0;

  while (index1 < size1 && index2 < size2) {
    if (arr1[index1] >= arr2[index2]) {
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

void mergeSort(int arr[], int size, bool isAscending) {
  int halfSize = size / 2;
  int* tmpArr;

  if (size <= 1) {
    return;
  }

  mergeSort(arr, halfSize, isAscending);
  mergeSort(arr + halfSize, size - halfSize, isAscending);

  tmpArr = (int*)malloc(size * sizeof(int));

  if (tmpArr == NULL) {
    exit(1);
  }

  if (isAscending) {
    mergeAscending(arr, halfSize, arr + halfSize, size - halfSize, tmpArr);
  } else {
    mergeDescending(arr, halfSize, arr + halfSize, size - halfSize, tmpArr);
  }
  copyArr(tmpArr, arr, size);
  free(tmpArr);

  return;
}

int** pointerSort(int* arr, unsigned int size, int ascend_flag) {
  int i;
  mergeSort(arr, size, (bool)ascend_flag);

  int** pointerArr = (int**)malloc(size * sizeof(int*));

  if (pointerArr == NULL) {
    exit(1);
  }

  for (i = 0; i < size; i++) {
    pointerArr[i] = &arr[i];
  }

  return pointerArr;
}

void printPointers(int** arr, unsigned int size) {
  int i;

  for (i = 0; i < size; i++) {
    printf("%d ", *arr[i]);
  }

  printf("\n");
}