#define _CRT_SECURE_NO_WARNINGS
#include "common.h"
#include "trees.h"

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

bool isValidInteger(char ch);
bool isValidOperator(char ch);
void printTreeInorder(Tree tr);
void printTreeInorderRec(TreeNode* root);
Tree BuildTreeFromArray(int* arr, int size);
TreeNode* BuildTreeFromArrayRec(int* arr, int size);
int findTreeHeightRec(TreeNode* root);
void printByLevels(Tree tr);
void buildDataByLevelsArray(TreeNode* root, SubList* dataByLevelsArray, int currentLevel);
void printDataByLevelsArray(SubList* dataByLevelsArray, int size);
void freeDataByLevelsArray(SubList* dataByLevelsArray, int size);
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

  tr = BuildTreeFromArray(arr, size); // the function from question 1
  printByLevels(tr);
  freeTree(tr);
}

TreeNode* createTreeNode(int data, TreeNode* left, TreeNode* right) {
  TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
  checkAllocation(newNode);

  newNode->data = data;
  newNode->left = left;
  newNode->right = right;

  freeTree(tr);
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

bool isValidInteger(char ch) {
  return (ch >= '0' && ch <= '9');
}

bool isValidOperator(char ch) {
  return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');
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
