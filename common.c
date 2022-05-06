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

/* Swaps position of strings in array (char**) */
void swap(Employee** a, Employee** b) {
  Employee* temp = *a;
  *a = *b;
  *b = temp;
}

/* Quick sort Employee* in array (char**) */
void quicksort(Employee** arr, unsigned int length) {
  unsigned int i, piv = 0;
  if (length <= 1)
    return;

  for (i = 0; i < length - 1; i++) {
    if (arr[i]->salary > arr[i + 1]->salary)
      swap(arr + i, arr + piv++);
  }
  // move pivot to "middle"
  swap(arr + piv, arr + length - 1);

  // recursively sort upper and lower
  quicksort(arr, piv++); // set length to current pvt and increase for next call
  quicksort(arr + piv, length - piv);
}