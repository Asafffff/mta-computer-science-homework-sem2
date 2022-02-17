#include <stdio.h>

void printMultiplicationBoard();
int getIntegerLength(int number);

int main() {
  printMultiplicationBoard();
}

int getIntegerLength(int number) {
  int length = 0;

  while (number > 0) {
    number /= 10;
    length++;
  }

  return length;
}

void printMultiplicationBoard() {
  int i, j;
  int maxMultiplier = 10;

  int columnSeparatorLength;

  for (i = 1; i <= maxMultiplier; i++) {
    for (j = 1; j <= maxMultiplier; j++) {
      columnSeparatorLength = getIntegerLength(j * maxMultiplier);
      columnSeparatorLength = j == 1 ? columnSeparatorLength : columnSeparatorLength + 1;
      printf("%*d", columnSeparatorLength, i * j);
    }
    printf("\n");
  }
}