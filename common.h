#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOT_FOUND -1

typedef struct _client {
  char id[9];     // “12345678”
  char phone[12]; // “054-1234567”
} Client;

typedef struct _short_client {
  unsigned char short_id[4];
  unsigned char short_phone[5];
} Short_client;

void checkAllocation(void* ptr);
void checkFile(FILE* file);
void* increaseArraySizeIfFull(void* arr, int* logSize, int* phySize, unsigned long sizeOfType);
