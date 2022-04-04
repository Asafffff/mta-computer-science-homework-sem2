#define _CRT_SECURE_NO_WARNINGS
#include "trees.h"

typedef int BOOL;
#define FALSE 0
#define TRUE 1
#define SIZE 100

typedef struct TreeNode {
  unsigned int data;
  struct TreeNode* right;
  struct TreeNode* left;
} TreeNode;

typedef struct Tree {
  TreeNode* root;
} Tree;

bool buildExpressionTree(char* expression, Tree* tree);
TreeNode* buildExpressionTreeRec(char* expression);
double calcExpression(Tree tr);
double calcExpressionRec(TreeNode* root);
char* createSubExpressionByIndices(char* expression, int startIndex, int endIndex);
bool isValidInteger(char ch);
bool isValidOperator(char ch);
int findParentOperatorIndex(char* expression);
// --------------------------------------------------
TreeNode* createTreeNode(int data, TreeNode* left, TreeNode* right);
void freeTree(Tree tr);
void freeTreeRec(TreeNode* root);
void checkAllocation(void* ptr);

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

bool buildExpressionTree(char* expression, Tree* tree) {
  tree->root = buildExpressionTreeRec(expression);

  return (tree->root != NULL);
}

TreeNode* buildExpressionTreeRec(char* expression) {
  int operatorIndex;
  int expressionLength = strlen(expression);
  if (expressionLength == 0) {
    return NULL;
  } else if (expressionLength == 1) {
    if (!(isValidInteger(expression[0]))) {
      printf("The input expression is not valid\n");
      exit(1);
    } else {
      int nodeData = expression[0] - '0';

      return createTreeNode(nodeData, NULL, NULL);
    }
  }

  operatorIndex = findParentOperatorIndex(expression);
  if (operatorIndex == -1) {
    return NULL;
  }

  char* leftSubExpression = createSubExpressionByIndices(expression, 1, operatorIndex - 1);
  char* rightSubExpression = createSubExpressionByIndices(expression, operatorIndex + 1, strlen(expression) - 2);

  TreeNode* leftNode = buildExpressionTreeRec(leftSubExpression);
  TreeNode* rightNode = buildExpressionTreeRec(rightSubExpression);

  TreeNode* root = createTreeNode(expression[operatorIndex], leftNode, rightNode);

  return root;
}

double calcExpression(Tree tr) {
  return calcExpressionRec(tr.root);
}

double calcExpressionRec(TreeNode* root) {
  if (root == NULL)
    return 0;

  double left = calcExpressionRec(root->left);
  double right = calcExpressionRec(root->right);

  switch (root->data) {
    case '+':
      return left + right;
    case '-':
      return left - right;
    case '*':
      return left * right;
    case '/':
      return left / right;
    case '%':
      return (int)left % (int)right;
    default:
      return root->data;
  }
}
