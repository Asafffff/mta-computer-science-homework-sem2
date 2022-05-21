#include "common.h"

void checkAllocation(void* ptr) {
  if (ptr == NULL) {
    exit(1);
  }
}

void checkFile(FILE* file) {
  if (file == NULL) {
    printf("Could not open file.\nExiting...");
    exit(1);
  }
}

/**
 * @brief Increases the size of the array, if it is full
 *
 * @param arr The array to be resized
 * @param logSize The logical size of the array
 * @param phySize The physical size of the array
 * @return void* The resized array, before casting to the original type
 */
void* increaseArraySizeIfFull(void* arr, int* logSize, int* phySize, unsigned long sizeOfType) {
  if (*logSize == *phySize) {
    (*phySize) *= 2;
    arr = realloc(arr, (*phySize) * sizeOfType);
    checkAllocation(arr);
  }

  return arr;
}

BYTE* compressStringInteger(char* integerAsString, int numOfBytes) {
  int i;
  BYTE* compressedString = (BYTE*)malloc(sizeof(BYTE) * numOfBytes);
  checkAllocation(compressedString);

  int stringLength = strlen(integerAsString);
  BYTE currentByte = 0x00;

  for (i = 0; i < stringLength; i++) {
    char currentDigit = integerAsString[i] - '0';

    // If the index is even, it should take the 4 leftmost bits
    if (i % 2 == 0) {
      currentByte |= currentDigit << 4;
    } else {
      currentByte |= currentDigit;

      // Append to compressedId and reset state
      compressedString[i / 2] = currentByte;
      currentByte = 0x00;
    }
  }

  return compressedString;
}
