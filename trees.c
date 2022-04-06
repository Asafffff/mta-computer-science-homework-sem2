#include "trees.h"
#include "common.h"

TreeNode* createTreeNode(int data, TreeNode* left, TreeNode* right) {
  TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
  checkAllocation(newNode);

  newNode->data = data;
  newNode->left = left;
  newNode->right = right;

  return newNode;
}

void freeTree(Tree tr) {
  freeTreeRec(tr.root);
}

void freeTreeRec(TreeNode* root) {
  if (root == NULL)
    return;
  else {
    freeTreeRec(root->left);
    freeTreeRec(root->right);
    free(root);
  }
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
