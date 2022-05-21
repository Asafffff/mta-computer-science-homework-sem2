#define _CRT_SECURE_NO_WARNINGS
#include "common.h"
#define SIZE 100
void main() {
  int* intArr;
  int intSize, intToFind;
  char **stringArr, stringToFind[SIZE];
  int stringSize;
  int res;

  // The user will enter the number of integers followed by the integers.
  intArr = getIntArr(&intSize);

  // The user will enter the integer to find
  scanf("%d", &intToFind);

  // The function searches the array using binSearch()
  res = intBinSearch(intArr, intSize, intToFind);

  if (res == 1)
    printf("The number %d was found\n", intToFind);

  else
    printf("The number %d was not found\n", intToFind);

  // The user will enter the number of strings (lines) followed by the strings.
  // You may assume that each line contains up to 99 characters.
  stringArr = getStringArr(&stringSize);

  // The user will enter the string to find
  gets(stringToFind);

  // The function searches the array using binSearch()
  res = stringBinSearch(stringArr, stringSize, stringToFind);

  if (res == 1)
    printf("The string %s was found\n", stringToFind);
  else
    printf("The string %s was not found\n", stringToFind);

  freeMemory(intArr, intSize, stringArr, stringSize);
}