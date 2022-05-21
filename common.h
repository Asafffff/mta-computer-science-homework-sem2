#ifndef _COMMON_H
#define _COMMON_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOT_FOUND -1
#define NUM_OF_BITS_IN_BYTE 8

typedef unsigned char BYTE;

void checkAllocation(void* ptr);
void checkFile(FILE* file);
void* increaseArraySizeIfFull(void* arr, int* logSize, int* phySize, unsigned long sizeOfType);
bool isBitOnByIndex(BYTE byte, unsigned int index);
int* filter(int* Numbers, int size, unsigned char* pred, int* new_size);
int* xorFilter(int* Numbers, int size, unsigned char* pred1, unsigned char* pred2, int* new_size);

#endif // _COMMON_H