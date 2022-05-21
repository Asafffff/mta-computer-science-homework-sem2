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

bool isBitOnByIndex(BYTE byte, unsigned int index) {
  BYTE mask = 0x01;
  mask <<= index;

  return (byte & mask) > 0;
}

/**
 * @brief filter, check an array of bits, pred1, and only append numbers that complies with that that only
 * the current bit is turned on.
 *
 * @param Numbers array of numbers
 * @param size size of Numbers array
 * @param pred1 first bits filter
 * @param new_size output parameter for the size of the new array
 * @return int* returned array
 */
int* filter(int* Numbers, int size, unsigned char* pred, int* new_size) {
  int i, j;

  int filteredNumbersLogSize = 0;
  int* filteredNumbers = (int*)malloc(size * sizeof(int));

  for (i = 0; i < size / 8; i++) {
    BYTE currentByte = pred[i];

    // Loop backwards from 7 to 0
    for (j = NUM_OF_BITS_IN_BYTE - 1; j >= 0; j--) {
      // Check if bit is on, on given index
      if (isBitOnByIndex(currentByte, NUM_OF_BITS_IN_BYTE - 1 - j)) {
        // append the correct number to the output array
        int currentNumber = Numbers[i * 8 + NUM_OF_BITS_IN_BYTE - 1 - j];
        filteredNumbers[filteredNumbersLogSize] = currentNumber;
        filteredNumbersLogSize++;
      }
    }
  }

  filteredNumbers = (int*)realloc(filteredNumbers, filteredNumbersLogSize * sizeof(int));

  *new_size = filteredNumbersLogSize;
  return filteredNumbers;
}

/**
 * @brief xorFilter, check two array of bits, pred1 and pred2, and only append numbers that complies with that that only
 * one of them is turned on.
 *
 * @param Numbers array of numbers
 * @param size size of Numbers array
 * @param pred1 first bits filter
 * @param pred2 second bits filter
 * @param new_size output parameter for the size of the new array
 * @return int* returned array
 */
int* xorFilter(int* Numbers, int size, unsigned char* pred1, unsigned char* pred2, int* new_size) {
  int i, j;

  int filteredNumbersLogSize = 0;
  int* filteredNumbers = (int*)malloc(size * sizeof(int));

  for (i = 0; i < size / 8; i++) {
    BYTE currentPred1Byte = pred1[i];
    BYTE currentPred2Byte = pred2[i];

    // Loop backwards from 7 to 0
    for (j = NUM_OF_BITS_IN_BYTE - 1; j >= 0; j--) {
      // Check each filter bit
      bool pred1BitIsOn = isBitOnByIndex(currentPred1Byte, NUM_OF_BITS_IN_BYTE - 1 - j);
      bool pred2BitIsOn = isBitOnByIndex(currentPred2Byte, NUM_OF_BITS_IN_BYTE - 1 - j);

      if ((pred1BitIsOn && !pred2BitIsOn) || (!pred1BitIsOn && pred2BitIsOn)) {
        // append the correct number to the output array
        int currentNumber = Numbers[i * 8 + NUM_OF_BITS_IN_BYTE - 1 - j];
        filteredNumbers[filteredNumbersLogSize] = currentNumber;
        filteredNumbersLogSize++;
      }
    }
  }

  filteredNumbers = (int*)realloc(filteredNumbers, filteredNumbersLogSize * sizeof(int));

  *new_size = filteredNumbersLogSize;
  return filteredNumbers;
}