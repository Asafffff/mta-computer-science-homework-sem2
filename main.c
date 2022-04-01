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

Tree BuildTreeFromArray(int* arr, int size);
TreeNode* BuildTreeFromArrayRec(int* arr, int size);
void printTreeInorder(Tree root);
void printTreeInorderRec(TreeNode* root);
bool buildExpressionTree(char* expression, Tree* tree);
double calcExpression(Tree tr);
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
