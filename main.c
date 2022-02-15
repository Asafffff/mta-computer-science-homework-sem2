#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct monom {
  int coefficient;
  int power;
} Monom;

Monom* scanPolynomialMonoms(int* monomsArraySize);
Monom* sumPolynomialMonomsWithSamePower(Monom polynomialMonomArray[], int* size);
void copyArr(Monom src[], Monom dest[], int size);
void mergeDescending(Monom arr1[], int size1, Monom arr2[], int size2, Monom tmpArr[]);
void mergeSort(Monom arr[], int size);
void printPolynomial(Monom polynomialMonomArray[], int monomsArraySize);

int main() {
  int monomsArraySize;
  Monom* polynomialMonomArray = scanPolynomialMonoms(&monomsArraySize);
  mergeSort(polynomialMonomArray, monomsArraySize);
  polynomialMonomArray = sumPolynomialMonomsWithSamePower(polynomialMonomArray, &monomsArraySize);
  printPolynomial(polynomialMonomArray, monomsArraySize);
  free(polynomialMonomArray);
}

void copyArr(Monom src[], Monom dest[], int size) {
  int i;

  for (i = 0; i < size; i++) {
    dest[i] = src[i];
  }

  return;
}

void mergeDescending(Monom arr1[], int size1, Monom arr2[], int size2, Monom tmpArr[]) {
  int index1, index2, writeIndex;
  index1 = index2 = writeIndex = 0;

  while (index1 < size1 && index2 < size2) {
    if (arr1[index1].power >= arr2[index2].power) {
      tmpArr[writeIndex] = arr1[index1];
      index1++;
    } else {
      tmpArr[writeIndex] = arr2[index2];
      index2++;
    }
    writeIndex++;
  }

  while (index1 < size1) {
    tmpArr[writeIndex] = arr1[index1];
    index1++;
    writeIndex++;
  }

  while (index2 < size2) {
    tmpArr[writeIndex] = arr2[index2];
    index2++;
    writeIndex++;
  }
}

void mergeSort(Monom arr[], int size) {
  int halfSize = size / 2;
  Monom* tmpArr;

  if (size <= 1) {
    return;
  }

  mergeSort(arr, halfSize);
  mergeSort(arr + halfSize, size - halfSize);

  tmpArr = (Monom*)malloc(size * sizeof(Monom));

  if (tmpArr == NULL) {
    exit(1);
  }

  mergeDescending(arr, halfSize, arr + halfSize, size - halfSize, tmpArr);
  copyArr(tmpArr, arr, size);
  free(tmpArr);

  return;
}

Monom* scanPolynomialMonoms(int* monomsArraySize) {
  int i, arrSize = 0;
  char lastInput;
  // TODO: Fix this to apply for unknown length
  int polynomialIntegerArray[MAX_LENGTH];
  Monom* polynomialMonomArray;

  while (scanf("%d%c", &polynomialIntegerArray[arrSize], &lastInput)) {
    arrSize++;
    if (lastInput == '\n') {
      break;
    }
  }

  *monomsArraySize = arrSize / 2;
  polynomialMonomArray = (Monom*)malloc(*monomsArraySize * sizeof(Monom));

  if (polynomialMonomArray == NULL) {
    exit(1);
  }

  for (i = 0; i < *monomsArraySize; i++) {
    polynomialMonomArray[i].coefficient = polynomialIntegerArray[2 * i];
    polynomialMonomArray[i].power = polynomialIntegerArray[2 * i + 1];
  }

  return polynomialMonomArray;
}

Monom* sumPolynomialMonomsWithSamePower(Monom polynomialMonomArray[], int* size) {
  int i, newSize = 0;
  Monom* modifiedPolynomialsArray = (Monom*)malloc((*size) * sizeof(Monom));

  for (i = 0; i < (*size); i++) {
    if (i == 0) {
      modifiedPolynomialsArray[newSize] = polynomialMonomArray[i];
      newSize++;
    } else {
      if (polynomialMonomArray[i].power == modifiedPolynomialsArray[newSize - 1].power) {
        modifiedPolynomialsArray[newSize - 1].coefficient += polynomialMonomArray[i].coefficient;
      } else {
        modifiedPolynomialsArray[newSize] = polynomialMonomArray[i];
        newSize++;
      }
    }
  }

  free(polynomialMonomArray);
  modifiedPolynomialsArray = (Monom*)realloc(modifiedPolynomialsArray, newSize * sizeof(Monom));
  *size = newSize;

  return modifiedPolynomialsArray;
}

void printPolynomial(Monom polynomialMonomArray[], int monomsArraySize) {
  int i, currentCoefficient, currentPower;
  bool isFirst = true;

  for (i = 0; i < monomsArraySize; i++) {
    currentCoefficient = polynomialMonomArray[i].coefficient;
    currentPower = polynomialMonomArray[i].power;

    if (currentCoefficient != 0) {
      if (currentCoefficient > 0) {
        if (isFirst) {
          isFirst = false;
        } else {
          printf("+");
        }
      }

      printf("%d", currentCoefficient);

      if (currentPower != 0) {
        printf("x");
      }
      if (currentPower != 0 && currentPower != 1) {
        printf("^%d", currentPower);
      }
    }
  }

  printf("\n");

  return;
}