#include "common.h"

void checkAllocation(void* ptr) {
  if (ptr == NULL) {
    exit(1);
  }
}

char* createSubExpressionByIndices(char* expression, int startIndex, int endIndex) {
  char* subExpression = (char*)malloc(sizeof(char) * (endIndex - startIndex + 1));
  checkAllocation(subExpression);

  int i;
  for (i = startIndex; i <= endIndex; i++) {
    subExpression[i - startIndex] = expression[i];
  }

  subExpression[i - startIndex] = '\0';

  return subExpression;
}

bool isValidInteger(char ch) {
  return (ch >= '0' && ch <= '9');
}

bool isValidOperator(char ch) {
  return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');
}

int findParentOperatorIndex(char* expression) {
  int index = 0;
  int lenStr = strlen(expression);
  bool skipOperator = false;
  char currentChar;
  int parenthesisCount = 0;

  while (index < lenStr) {
    currentChar = expression[index];

    if (currentChar == '(') {
      parenthesisCount++;
      if (parenthesisCount > 1) {
        skipOperator = true;
      }
    } else if (currentChar == ')') {
      parenthesisCount--;
      if (parenthesisCount == 1) {
        skipOperator = false;
      }
    } else if (!skipOperator && parenthesisCount == 1 && isValidOperator(currentChar)) {
      return index;
    }

    index++;
  }

  return -1;
}