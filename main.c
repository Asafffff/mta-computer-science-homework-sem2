#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROMAN_LENGTH 64
#define MAX_STRING_LENGTH 120

void printIntegerAsRomanString(int num);
void printFormattedIntegers(char* format, char* numbers);
void printIntegerAsBinaryString(int number);
int* extractNumbersFromStringToIntegerArray(char* str);
void fillArrayWithTokens(int arr[], char* str);
int countTokens(char* str);
bool isFormattingString(char* string);
void customPrintfFormatting(char* formattingString, int number);

int main() {
  printFormattedIntegers("%b in Binary is %o in Octal", "18 18");
}

void printIntegerAsRomanString(int num) {
  int del[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
  char* sym[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
  char res[MAX_ROMAN_LENGTH] = "\0";
  int i = 0;

  while (num) {
    while (num / del[i]) {
      strcat(res, sym[i]);
      num -= del[i];
    }
    i++;
  }

  printf(res);
}

void printIntegerAsBinaryString(int number) {
  if (number == 0) {
    return;
  }

  printIntegerAsBinaryString(number / 2);
  printf("%d", number % 2);
}

void printFormattedIntegers(char* format, char* numbers) {
  int numbersArrIndex = 0;
  int* numbersArr;
  char* formatAsSeparatedStrings;

  numbersArr = extractNumbersFromStringToIntegerArray(numbers);

  char* stringsArr;
  char copyOfString[MAX_STRING_LENGTH];
  strcpy(copyOfString, format);

  char* token;

  token = strtok(copyOfString, " ");
  while (token != NULL) {
    if (isFormattingString(token)) {
      customPrintfFormatting(token, numbersArr[numbersArrIndex]);
      printf(" ");
      numbersArrIndex++;
    } else {
      printf("%s ", token);
    }

    token = strtok(NULL, " ");
  }

  return;
}

int* extractNumbersFromStringToIntegerArray(char* str) {
  int numberOfTokens = 0;
  int* numbersArr;
  char copyOfString[MAX_STRING_LENGTH];

  strcpy(copyOfString, str);
  numberOfTokens = countTokens(copyOfString);
  numbersArr = (int*)malloc(numberOfTokens * sizeof(int));

  if (numbersArr == NULL) {
    exit(1);
  }

  strcpy(copyOfString, str);
  fillArrayWithTokens(numbersArr, copyOfString);

  return numbersArr;
}

int countTokens(char* str) {
  int count = 0;
  char* token;

  token = strtok(str, " ");
  while (token != NULL) {
    count++;
    token = strtok(NULL, " ");
  }

  return count;
}

void fillArrayWithTokens(int arr[], char* str) {
  char* token;
  int i = 0;

  token = strtok(str, " ");
  while (token != NULL) {
    arr[i] = atoi(token);
    token = strtok(NULL, " ");
    i++;
  }
}

bool isFormattingString(char* string) {
  return string[0] == '%';
}

void customPrintfFormatting(char* formattingString, int number) {
  switch (formattingString[1]) {
    case 'd':
      printf("%d", number);
      break;
    case 'x':
      printf("%x", number);
      break;
    case 'X':
      printf("%X", number);
      break;
    case 'o':
      printf("%o", number);
      break;
    case 'b':
      printIntegerAsBinaryString(number);
      break;
    case 'r':
      printIntegerAsRomanString(number);
      break;
    default:
      printf("#UNSUPPORTED_FORMAT# ");
      break;
  }
}