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

void sortLexicographically(char** strings, int numberOfStrings) {
  int i, j;

  quicksort(strings, numberOfStrings);

  return;
}

/* Swaps position of strings in array (char**) */
void swap(const char** a, const char** b) {
  const char* temp = *a;
  *a = *b;
  *b = temp;
}

/* Quick sort strings in array (char**) */
void quicksort(char const* arr[], unsigned int length) {
  unsigned int i, piv = 0;
  if (length <= 1)
    return;

  for (i = 0; i < length; i++) {
    // if curr str < pivot str, move curr into lower array and  lower++(pvt)
    if (strcmp(arr[i], arr[length - 1]) < 0) // use string in last index as pivot
      swap(arr + i, arr + piv++);
  }
  // move pivot to "middle"
  swap(arr + piv, arr + length - 1);

  // recursively sort upper and lower
  quicksort(arr, piv++); // set length to current pvt and increase for next call
  quicksort(arr + piv, length - piv);
}