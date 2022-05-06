#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct employee {
  int name_length;
  char* name;
  float salary;
} Employee;

void checkAllocation(void* ptr);
void checkFile(FILE* file);
void copyArr(Employee* src[], Employee* dest[], int size);
void merge(Employee* arr1[], int size1, Employee* arr2[], int size2, Employee* tmpArr[]);
void mergeSort(Employee* arr[], int size);