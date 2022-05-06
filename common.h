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