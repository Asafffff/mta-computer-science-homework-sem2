#include "lists.h"

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

void freeListRec(ListNode* listNode) {
  if (listNode == NULL)
    return;
  else {
    freeListRec(listNode->next);
    free(listNode);
  }
}

void printLeafListRec(ListNode* listNode) {
  if (listNode == NULL) {
    return;
  }

  printf("%d ", listNode->data);
  printLeafListRec(listNode->next);

  return;
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
