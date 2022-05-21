#define _CRT_SECURE_NO_WARNINGS
#include "common.h"

void main() {
  int i, pr, new_size, size;
  int* numbers;
  unsigned char *pred1, *pred2;
  int* some_numbers1;
  int* some_numbers2;

  printf("Please enter the number of numbers:\n");
  scanf("%d", &size);

  numbers = (int*)malloc(size * sizeof(int));

  if (numbers == NULL)
    exit(1);

  pred1 = (char*)malloc(size / 8 * sizeof(char));

  if (pred1 == NULL)
    exit(1);

  pred2 = (char*)malloc(size / 8 * sizeof(char));

  if (pred2 == NULL)
    exit(1);

  printf("Please enter the numbers:\n");

  for (i = 0; i < size; i++)
    scanf("%d", &numbers[i]);

  printf("Please enter the first filter bits in hexa:\n");

  for (i = 0; i < size / 8; i++) {
    scanf("%x", &pr);
    pred1[i] = (char)pr;
  }

  some_numbers1 = filter(numbers, size, pred1, &new_size);
  printf("The numbers selected are:\n");

  for (i = 0; i < new_size; i++)
    printf("%d ", some_numbers1[i]);

  printf("Please enter the second filter bits in hexa:\n");

  for (i = 0; i < size / 8; i++) {
    scanf("%x", &pr);
    pred2[i] = (char)pr;
  }

  some_numbers2 = xorFilter(numbers, size, pred1, pred2, &new_size);
  printf("The numbers selected are:\n");

  for (i = 0; i < new_size; i++)
    printf("%d ", some_numbers2[i]);

  free(numbers);
  free(some_numbers1);
  free(pred1);
  free(some_numbers2);
  free(pred2);
}