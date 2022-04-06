#define _CRT_SECURE_NO_WARNINGS
#include "common.h"
#include "trees.h"

typedef int BOOL;
#define FALSE 0
#define TRUE 1
#define SIZE 100

void main() {
  char str[SIZE];
  Tree tr;
  double res;
  BOOL expressionOK;

  printf("Please enter the expression: ");
  gets(str);
  expressionOK = buildExpressionTree(str, &tr);

  if (expressionOK == TRUE) {
    res = calcExpression(tr);
    printf("%s = %.2f", str, res);
  } else
    printf("The input expression is not valid\n");

  freeTree(tr);
}