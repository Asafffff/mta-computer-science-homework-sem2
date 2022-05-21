#ifndef _COMMON_H
#define _COMMON_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void freeMemory(int* intArr, int* scrambleIntArr, int intSize, char** stringArr, char** scrambleStringArr,
                int stringSize);

#endif // _COMMON_H