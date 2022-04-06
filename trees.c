#include "trees.h"

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

Tree BuildTreeFromArray(int* arr, int size) {
  Tree tr;

  tr.root = BuildTreeFromArrayRec(arr, size);

  return tr;
}

TreeNode* BuildTreeFromArrayRec(int* arr, int size) {
  int newNodeData = arr[size / 2];

  if (newNodeData == -1) {
    return NULL;
  }

  if (size == 1) {
    return createTreeNode(newNodeData, NULL, NULL);
  }

  TreeNode* leftNode = BuildTreeFromArrayRec(arr, (size / 2));
  TreeNode* rightNode = BuildTreeFromArrayRec(arr + (size / 2) + 1, size / 2);

  return createTreeNode(newNodeData, leftNode, rightNode);
}

void printTreeInorder(Tree tr) {
  printTreeInorderRec(tr.root);
}

void printTreeInorderRec(TreeNode* root) {
  if (root == NULL)
    return;

  printTreeInorderRec(root->left);
  printf("%d ", root->data);
  printTreeInorderRec(root->right);
}