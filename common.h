#ifndef _COMMON_H
#define _COMMON_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FOUND true
#define NOT_FOUND false
#define GT 1
#define EQ 0
#define LT -1
#define STRING_MAX_LENGTH 99

typedef unsigned char BYTE;

void checkAllocation(void* ptr);
void checkFile(FILE* file);
void* increaseArraySizeIfFull(void* arr, int* logSize, int* phySize, unsigned long sizeOfType);
void* scramble(void* arr, int ElemSize, int n, int* indArr);
int* getIntArr(int* intSize);
int* scrambleInt(int* intArr, int intSize, int* indArr);
void printIntArr(int* intArr, int intSize);
char** getStringArr(int* stringArrSize);
char** scrambleString(char** stringArr, int stringSize, int* indArr);
void printStringArr(char** stringArr, int stringSize);
void freeMemory(int* intArr, int intSize, char** stringArr, int stringSize);
int binSearch(void* Arr, int Size, int ElemSize, void* Item, int (*compare)(void*, void*));
int stringsCompare(void* a, void* b);
int intCompare(void* a, void* b);
bool intBinSearch(int* intArr, int intSize, int intToFind);
bool stringBinSearch(char** stringArr, int stringArrSize, char* stringToFind);
#endif // _COMMON_H