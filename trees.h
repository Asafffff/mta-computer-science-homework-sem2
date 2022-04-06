// #pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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