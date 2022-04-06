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

int findTreeHeightRec(TreeNode* root) {
  int leftHeight, rightHeight;
  if (root == NULL) {
    return -1;
  }

  leftHeight = findTreeHeightRec(root->left);
  rightHeight = findTreeHeightRec(root->right);

  return (max(leftHeight, rightHeight) + 1);
}

/**
 * Organize all data to a single array, who contains sub-arrays that is distinguished by levels.
 * For example:
 * The tree: 2 23 5 1 8 43 27
 * Will be separated as follows:
 * [ [1] , [23, 43] , [2, 5, 8, 27] ]
 *
 * Runtime evaluation:
 * - findTreeHeightRec: O(n)
 * - Allocation & for loop: O(log(n))
 * - buildDataByLevelsArray: O(n)
 * - printDataByLevelsArray: Two for loops, but 'n' nodes in total, so O(n)
 *
 * In total:
 * O(3n + log(n)) ~= O(n) as required.
 */
void printByLevels(Tree tr) {
  int i;
  int treeHeight = findTreeHeightRec(tr.root) + 1;

  SubList* dataByLevelsArray = (SubList*)malloc(treeHeight * sizeof(SubList));
  checkAllocation(dataByLevelsArray);

  for (i = 0; i < treeHeight; i++) {
    SubList newSubList = {.arr = NULL, .arrSize = 0};
    dataByLevelsArray[i] = newSubList;
  }

  buildDataByLevelsArray(tr.root, dataByLevelsArray, 0);

  printDataByLevelsArray(dataByLevelsArray, treeHeight);

  freeDataByLevelsArray(dataByLevelsArray, treeHeight);
}

void printDataByLevelsArray(SubList* dataByLevelsArray, int size) {
  int i, j;
  SubList currentSubList;

  for (i = 0; i < size; i++) {
    currentSubList = dataByLevelsArray[i];

    // Print sublist inner array
    for (j = 0; j < currentSubList.arrSize; j++) {
      printf("%d ", currentSubList.arr[j]);
    }
  }
}

void freeDataByLevelsArray(SubList* dataByLevelsArray, int size) {
  int i;
  SubList currentSubList;

  for (i = 0; i < size; i++) {
    currentSubList = dataByLevelsArray[i];

    if (currentSubList.arr != NULL) {
      free(currentSubList.arr);
    }
  }

  free(dataByLevelsArray);
}

void increaseSubListArrSizeByOne(SubList* subList) {
  subList->arrSize = subList->arrSize + 1;

  if (subList->arr == NULL) {
    subList->arr = (int*)malloc(subList->arrSize * sizeof(int));
  } else {
    subList->arr = realloc(subList->arr, subList->arrSize * sizeof(int));
  }

  return;
}

// O(n) as we have 'n' nodes, with basic operation executed on each
// (except reallocation, but it has been said in class that it is still makes it O(n))
void buildDataByLevelsArray(TreeNode* root, SubList* dataByLevelsArray, int currentLevel) {
  if (root == NULL) {
    return;
  }

  buildDataByLevelsArray(root->left, dataByLevelsArray, currentLevel + 1);
  buildDataByLevelsArray(root->right, dataByLevelsArray, currentLevel + 1);

  // Increase sublist array size and insert the data to the end of the sublist array
  SubList currentSubList = dataByLevelsArray[currentLevel];
  increaseSubListArrSizeByOne(&currentSubList);

  currentSubList.arr[currentSubList.arrSize - 1] = root->data;

  // Overwrite old sublist
  dataByLevelsArray[currentLevel] = currentSubList;

  return;
}
