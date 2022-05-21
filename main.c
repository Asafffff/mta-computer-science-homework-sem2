#define _CRT_SECURE_NO_WARNINGS
#include "common.h"

#define SIZE 100

void main() {
  int *intArr, *scrambleIntArr;
  int intSize;
  char **stringArr, **scrambleStringArr;
  int stringSize, i;
  int indArr[SIZE];

  // The user will enter the number of integers followed by the integers.
  intArr = getIntArr(&intSize);

  // The user will enter the indices
  for (i = 0; i < intSize; i++)
    scanf("%d", &indArr[i]);

  // The function scrambles the array using scramble()
  scrambleIntArr = scrambleInt(intArr, intSize, indArr);
  printIntArr(scrambleIntArr, intSize);

  // The user will enter the number of strings (lines) followed by the strings.
  // You may assume that each line contains up to 99 characters.
  stringArr = getStringArr(&stringSize);

  // The user will enter the indices
  for (i = 0; i < stringSize; i++)
    scanf("%d", &indArr[i]);

  // The function scrambles the array using scramble()
  scrambleStringArr = scrambleString(stringArr, stringSize, indArr);

  printStringArr(scrambleStringArr, stringSize);

  freeMemory(intArr, scrambleIntArr, intSize, stringArr, scrambleStringArr, stringSize);
}