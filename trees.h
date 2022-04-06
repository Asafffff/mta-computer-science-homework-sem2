#pragma once
#include "common.h"
#include "lists.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEFT 0
#define RIGHT 1

typedef struct treeNode {
  int data;
  struct treeNode* parent;
  struct treeNode* left;
  struct treeNode* right;
} TreeNode;

typedef struct tree {
  TreeNode* root;
  List leafList; /*רשימה מקושרת של כל העלים בעץ*/
} Tree;

Tree BuildTreeFromArrayWithLeafList(int* arr, int size);
TreeNode* BuildTreeFromArrayWithLeafListRec(Tree* tr, int* arr, int size);
void updateSubNodesParents(TreeNode* node);
Tree AddLeaf(Tree tr, TreeNode* p, int branchSelect, int data);
TreeNode* findParent(Tree tr, int parentData, int branchSelect);
TreeNode* findParentRec(TreeNode* root, int parentData, int branchSelect);
void printTreeInorder(Tree tr);
void printTreeInorderRec(TreeNode* root);
void printLeafList(Tree tr);
TreeNode* findParentInSubnodes(TreeNode* root, int parentData, int branchSelect);
TreeNode* createTreeNode(int data, TreeNode* parent, TreeNode* left, TreeNode* right);
void freeTree(Tree tr);
void freeTreeRec(TreeNode* root);