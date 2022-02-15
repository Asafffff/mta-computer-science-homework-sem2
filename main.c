#include <stdio.h>

void printMultiplicationBoard();
int getIntegerLength(int number);

int main() {
  int maxMultiplier;

  printf("Please insert max multiplier: ");
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

  int separatorLength = getIntegerLength(maxMultiplier) + 1;

  for (i = 1; i <= maxMultiplier; i++) {
    for (j = 1; j <= maxMultiplier; j++) {
      printf("%*d ", separatorLength, i * j);
    }
    printf("\n");
  }
}