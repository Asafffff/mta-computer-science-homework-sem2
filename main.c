#include <stdio.h>

void printMultiplicationBoard();
int getIntegerLength(int number);

int main() {
  int maxMultiplier;

  printf("Please enter number:\n");
  scanf("%d", &maxMultiplier);

  printMultiplicationBoard(maxMultiplier);
}

int getIntegerLength(int number) {
  int length = 0;

  while (number > 0) {
    number /= 10;
    length++;
  }

  return length;
}

void printMultiplicationBoard(int maxMultiplier) {
  int i, j;

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