
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

  int separatorLength = getIntegerLength(maxMultiplier) + 1;

  for (i = 1; i <= maxMultiplier; i++) {
    for (j = 1; j <= maxMultiplier; j++) {
      printf("%*d ", separatorLength, i * j);
    }
    printf("\n");
  }
}