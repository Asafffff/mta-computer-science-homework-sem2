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
void swap(Employee** a, Employee** b);
void quicksort(Employee** arr, unsigned int length);