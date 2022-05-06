#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
  char* name;
  int average;
  long fileOffset;
} STUDENT;

void checkAllocation(void* ptr);
void checkFile(FILE* file);
void copyArr(STUDENT* src[], STUDENT* dest[], int size);
void merge(STUDENT* arr1[], int size1, STUDENT* arr2[], int size2, STUDENT* tmpArr[]);
void mergeSort(STUDENT* arr[], int size);