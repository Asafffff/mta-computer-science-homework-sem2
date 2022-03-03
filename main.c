#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int RemoveFromStrArray(char*** str_array, unsigned int str_array_size, char** ptr_to_chars_array);
void printArray(char** str_array, unsigned int str_array_size);
void freeArray(char** str_array, unsigned int str_array_size);
char* getInputString();
void shiftStringAndMatchingPointersLeftByOne(char* str, int startIndex, char** ptr_to_chars_array);
void shiftStringArrayLeftByOne(char** strArray, int arraySize, int startIndex);
int getPointerArraySize(char** ptr_to_chars_array);
char** getStrArrayInput(unsigned int* str_array_size);
char** setPtrToCharsArray(char** str_array);
void checkMemoryAllocation(void* ptr);
int deleteEmptyStrings(char** str_array, unsigned int str_array_size);

char** setPtrToCharsArray(char** str_array) {
  char** res;
  int size, i;
  int str_array_row, str_array_col;

  scanf(" %d", &size); // Get number of ptrs

  res = (char**)malloc(sizeof(char*) * (size + 1)); // Add 1 for NULL at the end

  for (i = 0; i < size; i++) {
    scanf(" %d", &str_array_row);
    scanf(" %d", &str_array_col);
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

void shiftStringAndMatchingPointersLeftByOne(char* str, int startIndex, char** ptr_to_chars_array) {
  int i, ptrToCharsArrIndex = 0;
  char* currentPointer;

  for (i = startIndex; i < strlen(str); i++) {
    // Shift string
    str[i] = str[i + 1];

    // Shift pointers of the same string, if needed
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
          shiftStringAndMatchingPointersLeftByOne(currentString, j, ptr_to_chars_array);
          currentPointerIndex++;
        }
      }
    }
  }

  // Loop over strings array, delete empty strings
  deletedStringsCount = deleteEmptyStrings(*str_array, str_array_size);

  return deletedStringsCount;
}

int deleteEmptyStrings(char** str_array, unsigned int str_array_size) {
  int i, deletedStringsCount = 0;
  char* currentString;

  for (i = 0; i < str_array_size - deletedStringsCount; i++) {
    currentString = str_array[i];
    if (strlen(currentString) == 0) {
      shiftStringArrayLeftByOne(str_array, str_array_size - deletedStringsCount, i);
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
  int stringArrayLogicalSize = 0, stringArrayPhysicalSize = 1;
  int inputNumberOfWords, inputStringLength;
  char* inputString;
  char** stringArray = (char**)malloc(1 * sizeof(char*));

  checkMemoryAllocation(stringArray);

  scanf(" %d", &inputNumberOfWords);
  getchar();

  for (int i = 0; i < inputNumberOfWords; i++) {
    inputString = getInputString();
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

  *str_array_size = stringArrayLogicalSize;
  return stringArray;
}

void checkMemoryAllocation(void* ptr) {
  if (ptr == NULL) {
    printf("Memory allocation failed!\n");
    exit(1);
  }
}

char* getInputString() {
  int maxStringLength = 1, stringWriteIndex = 0;
  char currentChar;
  char* inputString = (char*)malloc(maxStringLength * sizeof(char));

  checkMemoryAllocation(inputString);

  currentChar = getchar();
  while (currentChar != '\n') {
    if (stringWriteIndex == maxStringLength) {
      maxStringLength *= 2;
      inputString = (char*)realloc(inputString, maxStringLength * sizeof(char));
      checkMemoryAllocation(inputString);
    }

    inputString[stringWriteIndex] = currentChar;

    stringWriteIndex++;
    currentChar = getchar();
  }
  inputString[stringWriteIndex] = '\0';
  inputString = (char*)realloc(inputString, (stringWriteIndex + 1) * sizeof(char));

  return inputString;
}