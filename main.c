#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
// --------------------------------------------------
TreeNode* createTreeNode(int data, TreeNode* left, TreeNode* right);
void freeTree(Tree tr);
void freeTreeRec(TreeNode* root);
void checkAllocation(void* ptr);
// --------------------------------------------------

void main() {
  int size, i;
  int arr[SIZE];
  Tree tr;
  printf("Please enter the number of items: ");
  scanf("%d", &size);

  for (i = 0; i < size; i++)
    scanf("%d", &arr[i]);

  tr = BuildTreeFromArray(arr, size);

  printf("The tree in inorder (LDR) format:\n");
  printTreeInorder(tr); // Print the tree in-order (LDR)
  freeTree(tr);
}

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

void checkAllocation(void* ptr) {
  if (ptr == NULL) {
    exit(1);
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