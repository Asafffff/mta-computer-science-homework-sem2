#pragma once
#include "common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define SIZE 100

typedef struct subList {
  int* arr;
  int arrSize;
} SubList;

typedef struct treeNode {
  int data;
  struct treeNode* left;
  struct treeNode* right;
} TreeNode;

typedef struct tree {
  TreeNode* root;
} Tree;

void printTreeInorder(Tree tr);
void printTreeInorderRec(TreeNode* root);
Tree BuildTreeFromArray(int* arr, int size);
TreeNode* BuildTreeFromArrayRec(int* arr, int size);
int findTreeHeightRec(TreeNode* root);
void printByLevels(Tree tr);
void buildDataByLevelsArray(TreeNode* root, SubList* dataByLevelsArray, int currentLevel);
void printDataByLevelsArray(SubList* dataByLevelsArray, int size);
void freeDataByLevelsArray(SubList* dataByLevelsArray, int size);
TreeNode* createTreeNode(int data, TreeNode* left, TreeNode* right);
void freeTree(Tree tr);
void freeTreeRec(TreeNode* root);