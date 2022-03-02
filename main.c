#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 30

unsigned int RemoveFromStrArray(char*** str_array, unsigned int str_array_size, char** ptr_to_chars_array);
void printArray(char** str_array, unsigned int str_array_size);
void freeArray(char** str_array, unsigned int str_array_size);
void shiftStringLeftByOne(char* str, int startIndex, char** ptr_to_chars_array);
void shiftStringArrayLeftByOne(char** strArray, int arraySize, int startIndex);
int getPointerArraySize(char** ptr_to_chars_array);
char** getStrArrayInput(unsigned int* str_array_size);
char** setPtrToCharsArray(char** str_array);
void checkMemoryAllocation(void* ptr);

char** setPtrToCharsArray(char** str_array) {
  char** res;
  int size, i;
  int str_array_row, str_array_col;

  scanf("%d", &size); // Get number of ptrs

  res = (char**)malloc(sizeof(char*) * (size + 1)); // Add 1 for NULL at the end

  for (i = 0; i < size; i++) {
    scanf("%d", &str_array_row);
    scanf("%d", &str_array_col);
    res[i] = str_array[str_array_row] + str_array_col;
  }

  res[size] = NULL; // Set the last one to NULL

  return res;
}

int main() {
  char** str_array;
  unsigned int str_array_size;
  char** ptr_to_chars_array;
  unsigned int res;

  // Get the size and strings from user (can't assume max size for each string)
  str_array = getStrArrayInput(&str_array_size);
  ptr_to_chars_array = setPtrToCharsArray(str_array);
  res = RemoveFromStrArray(&str_array, str_array_size, ptr_to_chars_array);

  printArray(str_array, str_array_size - res);

  // Free memory
  freeArray(str_array, str_array_size - res);
  free(ptr_to_chars_array);
  str_array = NULL;
  ptr_to_chars_array = NULL;

  return 0;
}

void shiftStringLeftByOne(char* str, int startIndex, char** ptr_to_chars_array) {
  int i, ptrToCharsArrIndex = 0;
  char* currentPointer;

  for (i = startIndex; i < strlen(str); i++) {
    str[i] = str[i + 1];

    if (i != startIndex) {
      currentPointer = ptr_to_chars_array[ptrToCharsArrIndex];
      while (currentPointer != NULL) {
        if (currentPointer == &str[i]) {
          currentPointer -= sizeof(char);
          ptr_to_chars_array[ptrToCharsArrIndex] = currentPointer;
        }

        ptrToCharsArrIndex++;
        currentPointer = ptr_to_chars_array[ptrToCharsArrIndex];
      }
    }
    ptrToCharsArrIndex = 0;
  }
}

void shiftStringArrayLeftByOne(char** strArray, int arraySize, int startIndex) {
  int i;

  for (i = startIndex; i < arraySize - 1; i++) {
    strcpy(strArray[i], strArray[i + 1]);
  }

  free(strArray[arraySize - 1]);
  strArray[arraySize - 1] = NULL;
}

unsigned int RemoveFromStrArray(char*** str_array, unsigned int str_array_size, char** ptr_to_chars_array) {
  int i, j, currentPointerIndex, pointerArraySize, stringLength, deletedStringsCount = 0;
  char *currentString, *currentCharAddress, *currentPointerAddress;

  currentPointerIndex = 0;
  currentPointerAddress = ptr_to_chars_array[currentPointerIndex];

  // Loop over pointers array
  while (currentPointerAddress != NULL) {
    // Loop over strings array
    for (i = 0; i < str_array_size; i++) {
      currentString = (*str_array)[i];
      stringLength = strlen(currentString);
      // Loop over characters in string
      for (j = 0; j <= stringLength; j++) {
        currentCharAddress = &currentString[j];
        currentPointerAddress = ptr_to_chars_array[currentPointerIndex];
        if (currentCharAddress == currentPointerAddress) {
          shiftStringLeftByOne(currentString, j, ptr_to_chars_array);
          currentPointerIndex++;
        }
      }
    }
  }

  // Loop over strings array, delete empty strings
  for (i = 0; i < str_array_size - deletedStringsCount; i++) {
    currentString = (*str_array)[i];
    if (strlen(currentString) == 0) {
      shiftStringArrayLeftByOne(*str_array, str_array_size - deletedStringsCount, i);
      deletedStringsCount++;
      i--;
    }
  }

  return deletedStringsCount;
}

void printArray(char** str_array, unsigned int str_array_size) {
  int i;

  for (i = 0; i < str_array_size; i++) {
    printf("%s\n", str_array[i]);
  }
}

void freeArray(char** str_array, unsigned int str_array_size) {
  int i;

  for (i = 0; i < str_array_size; i++) {
    free(str_array[i]);
    str_array[i] = NULL;
  }

  free(str_array);
}

char** getStrArrayInput(unsigned int* str_array_size) {
  int stringArrayLogicalSize = 0, stringArrayPhysicalSize = 1, inputStringLength, inputNumberOfWords;
  char* inputString = (char*)malloc(MAX_STRING_LENGTH * sizeof(char));
  char** stringArray = (char**)malloc(1 * sizeof(char*));

  checkMemoryAllocation(inputString);
  checkMemoryAllocation(stringArray);

  scanf("%d", &inputNumberOfWords);

  for (int i = 0; i < inputNumberOfWords; i++) {
    scanf("%s", inputString);
    inputStringLength = strlen(inputString);

    if (stringArrayLogicalSize == stringArrayPhysicalSize) {
      stringArrayPhysicalSize *= 2;
      stringArray = (char**)realloc(stringArray, stringArrayPhysicalSize * sizeof(char*));
      checkMemoryAllocation(stringArray);
    }

    stringArray[stringArrayLogicalSize] = (char*)malloc((inputStringLength + 1) * sizeof(char));
    checkMemoryAllocation(stringArray[stringArrayLogicalSize]);

    strcpy(stringArray[stringArrayLogicalSize], inputString);

    stringArrayLogicalSize++;
  }

  free(inputString);

  *str_array_size = stringArrayLogicalSize;
  return stringArray;
}

void checkMemoryAllocation(void* ptr) {
  if (ptr == NULL) {
    printf("Memory allocation failed!\n");
    exit(1);
  }
}
