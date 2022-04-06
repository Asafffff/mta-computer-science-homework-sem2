#include "trees.h"

TreeNode* createTreeNode(int data, TreeNode* parent, TreeNode* left, TreeNode* right) {
  TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
  checkAllocation(newNode);

  newNode->data = data;
  newNode->parent = parent;
  newNode->left = left;
  newNode->right = right;

  return newNode;
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
