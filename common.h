#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOT_FOUND -1

typedef struct student {
  char* name;
  int average;
  long fileOffset;
} STUDENT;

void checkAllocation(void* ptr);
void checkFile(FILE* file);
void* increaseArraySizeIfFull(void* arr, int* logSize, int* phySize, unsigned long sizeOfType);
int gradesBinarySearchByOffsets(FILE* studentsFile, int arr[], int leftInd, int rightInd, int wantedGrade);