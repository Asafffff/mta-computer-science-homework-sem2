#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkAllocation(void* ptr);
void checkFile(FILE* file);
void sortLexicographically(char** strings, int numberOfStrings);
void swap(char** a, char** b);
void quicksort(char** arr, unsigned int length);