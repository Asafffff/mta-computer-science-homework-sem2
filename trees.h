#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
TreeNode* createTreeNode(int data, TreeNode* left, TreeNode* right);
void freeTree(Tree tr);
void freeTreeRec(TreeNode* root);