#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct monom {
  int coefficient;
  int power;
} Monom;

Monom* getPolynom(int* monomsArraySize);
Monom* sumPolynomialMonomsWithSamePower(Monom polynomialMonomArray[], int* size);
void printPolySum(Monom* polynom1, int monomsArraySize1, Monom* polynom2, int monomsArraySize2);
void printPolyMul(Monom* polynom1, int monomsArraySize1, Monom* polynom2, int monomsArraySize2);
void copyArr(Monom src[], Monom dest[], int size);
void mergeDescending(Monom arr1[], int size1, Monom arr2[], int size2, Monom tmpArr[]);
void mergeSort(Monom arr[], int size);
void printPolynomial(Monom polynomialMonomArray[], int monomsArraySize);

void main() {
  Monom *polynom1, *polynom2;              // The input polynoms
  unsigned int polynom1Size, polynom2Size; // The size of each polynom

  printf("Please enter the first polynom:\n");
  polynom1 = getPolynom(&polynom1Size); // get polynom 1

  printf("Please enter the second polynom:\n");
  polynom2 = getPolynom(&polynom2Size); // get polynom 2

  printf("The multiplication of the polynoms is:\n"); // print the multiplication
  printPolyMul(polynom1, polynom1Size, polynom2, polynom2Size);
  printf("\n");

  printf("The sum of the polynoms is:\n"); // print the sum
  printPolySum(polynom1, polynom1Size, polynom2, polynom2Size);
  printf("\n");

  free(polynom1); // releasing all memory allocations
  free(polynom2);
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

Monom* getPolynom(int* monomsArraySize) {
  int i, arrSize = 0;
  char lastInput;
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

      if (currentCoefficient != 1) {
        if (currentCoefficient == -1 && currentPower != 0) {
          printf("-");
        } else {
          printf("%d", currentCoefficient);
        }
      }

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

void printPolySum(Monom* polynom1, int monomsArraySize1, Monom* polynom2, int monomsArraySize2) {
  Monom* polynom1Copy = (Monom*)malloc(monomsArraySize1 * sizeof(Monom));
  Monom* polynom2Copy = (Monom*)malloc(monomsArraySize2 * sizeof(Monom));
  Monom* polynomSum = (Monom*)malloc((monomsArraySize1 + monomsArraySize2) * sizeof(Monom));
  int i, j, polynomSumSize;

  copyArr(polynom1, polynom1Copy, monomsArraySize1);
  copyArr(polynom2, polynom2Copy, monomsArraySize2);

  mergeSort(polynom1Copy, monomsArraySize1);
  mergeSort(polynom2Copy, monomsArraySize2);

  polynomSumSize = monomsArraySize1 + monomsArraySize2;
  mergeDescending(polynom1Copy, monomsArraySize1, polynom2Copy, monomsArraySize2, polynomSum);

  polynomSum = sumPolynomialMonomsWithSamePower(polynomSum, &polynomSumSize);

  printPolynomial(polynomSum, polynomSumSize);

  free(polynom1Copy);
  free(polynom2Copy);
  free(polynomSum);

  return;
}

void printPolyMul(Monom* polynom1, int monomsArraySize1, Monom* polynom2, int monomsArraySize2) {
  int i, j, polynomMulSize, polynomMulWriteIndex = 0;
  polynomMulSize = monomsArraySize1 * monomsArraySize2;

  Monom* polynomMul = (Monom*)malloc(polynomMulSize * sizeof(Monom));

  for (i = 0; i < monomsArraySize1; i++) {
    for (j = 0; j < monomsArraySize2; j++) {
      polynomMul[polynomMulWriteIndex].coefficient = polynom1[i].coefficient * polynom2[j].coefficient;
      polynomMul[polynomMulWriteIndex].power = polynom1[i].power + polynom2[j].power;
      polynomMulWriteIndex++;
    }
  }

  mergeSort(polynomMul, polynomMulSize);

  polynomMul = sumPolynomialMonomsWithSamePower(polynomMul, &polynomMulSize);

  printPolynomial(polynomMul, polynomMulSize);

  free(polynomMul);

  return;
}