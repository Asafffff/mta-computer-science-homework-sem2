#define _CRT_SECURE_NO_WARNINGS
#include "common.h"
#include "trees.h"

#define LEFT 0
#define RIGHT 1
#define SIZE 100

typedef struct listNode {
  int data;
  struct listNode* next;
} ListNode;

typedef struct list {
  ListNode* head;
  ListNode* tail;
} List;

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
bool isValidInteger(char ch);
bool isValidOperator(char ch);
void updateSubNodesParents(TreeNode* node);
Tree AddLeaf(Tree tr, TreeNode* p, int branchSelect, int data);
TreeNode* findParent(Tree tr, int parentData, int branchSelect);
TreeNode* findParentRec(TreeNode* root, int parentData, int branchSelect);
void printTreeInorder(Tree tr);
void printTreeInorderRec(TreeNode* root);
void printLeafList(Tree tr);
void printLeafListRec(ListNode* listNode);
TreeNode* findParentInSubnodes(TreeNode* root, int parentData, int branchSelect);
// --------------------------------------------------
TreeNode* createTreeNode(int data, TreeNode* parent, TreeNode* left, TreeNode* right);
ListNode* createListNode(int data, ListNode* next);
void insertDataToStartOfList(List* list, int data);
void insertDataToEndOfList(List* list, int data);
void insertNodeToStartOfList(List* list, ListNode* node);
void insertNodeToEndOfList(List* list, ListNode* node);
void initEmptyList(List* list);
void freeTree(Tree tr);
void freeTreeRec(TreeNode* root);
void freeListRec(ListNode* listNode);
void checkAllocation(void* ptr);
// --------------------------------------------------

void main() {
  int size, i;
  int arr[SIZE];
  Tree tr;
  TreeNode* p;
  int parentData, data, branchSelect;

  printf("Please enter the number of items: ");
  scanf("%d", &size);

  for (i = 0; i < size; i++)
    scanf("%d", &arr[i]);

  scanf("%d%d%d", &parentData, &data, &branchSelect);

  tr = BuildTreeFromArrayWithLeafList(arr, size); // the array is given as described in question 1

  // scan the tree inorder (LDR) and find the first parent (a node with parentData as data) that has no child in
  // branchSelect
  p = findParent(tr, parentData, branchSelect);
  tr = AddLeaf(tr, p, branchSelect, data);

  printTreeInorder(tr); // Print the tree in-order (LDR)
  printf("\n");
  printLeafList(tr); // Print the leaves from left to right

  freeTree(tr);
}

TreeNode* createTreeNode(int data, TreeNode* parent, TreeNode* left, TreeNode* right) {
  TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
  checkAllocation(newNode);

  newNode->data = data;
  newNode->parent = parent;
  newNode->left = left;
  newNode->right = right;

  return newNode;
}

ListNode* createListNode(int data, ListNode* next) {
  ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
  checkAllocation(newNode);

  newNode->data = data;
  newNode->next = next;

  return newNode;
}

void insertNodeToStartOfList(List* list, ListNode* node) {
  node->next = list->head;
  list->head = node;

  return;
}

void insertNodeToEndOfList(List* list, ListNode* node) {
  if (list->head == NULL) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }

  return;
}

void insertDataToStartOfList(List* list, int data) {
  ListNode* newNode = createListNode(data, NULL);

  insertNodeToStartOfList(list, newNode);
  return;
}

void insertDataToEndOfList(List* list, int data) {
  ListNode* newNode = createListNode(data, NULL);

  insertNodeToEndOfList(list, newNode);
  return;
}

void initEmptyList(List* list) {
  list->head = NULL;
  list->tail = NULL;
}

void freeTree(Tree tr) {
  freeTreeRec(tr.root);
  freeListRec(tr.leafList.head);
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

void freeListRec(ListNode* listNode) {
  if (listNode == NULL)
    return;
  else {
    freeListRec(listNode->next);
    free(listNode);
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

void printLeafList(Tree tr) {
  printLeafListRec(tr.leafList.head);
}

void printLeafListRec(ListNode* listNode) {
  if (listNode == NULL) {
    return;
  }

  printf("%d ", listNode->data);
  printLeafListRec(listNode->next);

  return;
}

void updateSubNodesParents(TreeNode* node) {
  if (node->left != NULL) {
    node->left->parent = node;
  }
  if (node->right != NULL) {
    node->right->parent = node;
  }
}

Tree BuildTreeFromArrayWithLeafList(int* arr, int size) {
  Tree tr;
  initEmptyList(&tr.leafList);

  tr.root = BuildTreeFromArrayWithLeafListRec(&tr, arr, size);

  return tr;
}

TreeNode* BuildTreeFromArrayWithLeafListRec(Tree* tr, int* arr, int size) {
  TreeNode* parentNode = NULL;
  int newNodeData = arr[size / 2];

  if (newNodeData == -1) {
    return NULL;
  }

  if (size == 1) {
    insertDataToEndOfList(&(tr->leafList), newNodeData);
    parentNode = createTreeNode(newNodeData, NULL, NULL, NULL);
    return parentNode;
  }

  TreeNode* leftNode = BuildTreeFromArrayWithLeafListRec(tr, arr, (size / 2));
  TreeNode* rightNode = BuildTreeFromArrayWithLeafListRec(tr, arr + (size / 2) + 1, size / 2);

  if (leftNode == NULL && rightNode == NULL) {
    insertDataToEndOfList(&(tr->leafList), newNodeData);
  }

  parentNode = createTreeNode(newNodeData, NULL, leftNode, rightNode);
  updateSubNodesParents(parentNode);

  return parentNode;
}

bool replaceListNodeInLeafListRec(ListNode* listNode, int prevNodeData, int newNodeData) {
  if (listNode == NULL) {
    return false;
  }

  if (listNode->data == prevNodeData) {
    listNode->data = newNodeData;
    return true;
  } else {
    return replaceListNodeInLeafListRec(listNode->next, prevNodeData, newNodeData);
  }
}

Tree AddLeaf(Tree tr, TreeNode* p, int branchSelect, int data) {
  TreeNode* newNode = createTreeNode(data, p, NULL, NULL);
  if (branchSelect == LEFT) {
    p->left = newNode;
  } else if (branchSelect == RIGHT) {
    p->right = newNode;
  } else {
    printf("Wrong branchSelect option. Exiting...");
    exit(1);
  }

  bool isReplaced = replaceListNodeInLeafListRec(tr.leafList.head, p->data, data);

  if (!isReplaced) {
    if (branchSelect == LEFT) {
      insertDataToStartOfList(&(tr.leafList), data);
    } else if (branchSelect == RIGHT) {
      insertDataToEndOfList(&(tr.leafList), data);
    }
  }

  return tr;
}

TreeNode* findParent(Tree tr, int parentData, int branchSelect) {
  return findParentRec(tr.root, parentData, branchSelect);
}

TreeNode* findParentRec(TreeNode* root, int parentData, int branchSelect) {
  int nodeData;

  if (root == NULL) {
    return NULL;
  }

  nodeData = root->data;

  if (nodeData != parentData) {
    return findParentInSubnodes(root, parentData, branchSelect);
  }

  switch (branchSelect) {
    case LEFT:
      if (root->left == NULL)
        return root;
    case RIGHT:
      if (root->right == NULL)
        return root;
    default:
      return findParentInSubnodes(root, parentData, branchSelect);
  }
}

TreeNode* findParentInSubnodes(TreeNode* root, int parentData, int branchSelect) {
  TreeNode *leftNode = NULL, *rightNode = NULL;

  leftNode = findParentRec(root->left, parentData, branchSelect);
  if (leftNode != NULL) {
    return leftNode;
  } else {
    rightNode = findParentRec(root->right, parentData, branchSelect);
    return rightNode;
  };
}
