#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode {
  int* dataPtr;
  struct listNode* next;
} ListNode;

typedef struct list {
  ListNode* head;
  ListNode* tail;
} List;

List getList();
List merge(List lst1, List lst2);
void printList(List* lst);

// --------------------------------------------------
void freeList(List* lst);
void makeEmptyList(List* lst);
bool isEmptyList(List lst);
ListNode* createNewListNode(int data, ListNode* next);
void insertDataToEndList(List* lst, int data);
void insertNodeToEndList(List* lst, ListNode* newTail);
void checkAllocation(void* ptr);
// --------------------------------------------------

void main() {

  List lst1, lst2, mergedList;

  lst1 = getList();
  lst2 = getList();

  mergedList = merge(lst1, lst2);

  printf("Merged list:\n");
  printList(&mergedList);

  freeList(&mergedList);
}

List getList() {
  List res;
  int size, num, i;

  makeEmptyList(&res);

  printf("Please enter the number of items to be entered:\n");
  scanf("%d", &size);

  printf("Please enter the numbers:\n");
  for (i = 0; i < size; i++) {
    scanf("%d", &num);
    insertDataToEndList(&res, num);
  }

  return res;
}

void makeEmptyList(List* lst) {
  lst->head = lst->tail = NULL;
}

ListNode* createNewListNode(int data, ListNode* next) {
  ListNode* result;

  result = (ListNode*)malloc(sizeof(ListNode));
  checkAllocation(result);

  result->dataPtr = (int*)malloc(sizeof(int));
  *(result->dataPtr) = data;
  result->next = next;

  return result;
}

void insertDataToEndList(List* lst, int data) {
  ListNode* result = createNewListNode(data, NULL);

  insertNodeToEndList(lst, result);
}

void insertNodeToEndList(List* lst, ListNode* newTail) {
  newTail->next = NULL;

  if (isEmptyList(*lst))
    lst->head = lst->tail = newTail;
  else {
    lst->tail->next = newTail;
    lst->tail = newTail;
  }
}

void freeList(List* lst) {
  ListNode *curr = (*lst).head, *next;

  while (curr != NULL) {
    next = curr->next;
    free(curr->dataPtr);
    free(curr);
    curr = next;
  }
}

bool isEmptyList(List lst) {
  return lst.head == NULL;
}

List merge(List lst1, List lst2) {
  List resultList;
  makeEmptyList(&resultList);

  int list1NodeData, list2NodeData;

  ListNode* currentList1Node = lst1.head;
  ListNode* currentList2Node = lst2.head;
  ListNode* tmpNextNode = NULL;

  while (currentList1Node != NULL && currentList2Node != NULL) {
    list1NodeData = *(currentList1Node->dataPtr);
    list2NodeData = *(currentList2Node->dataPtr);

    if (list1NodeData > list2NodeData) {
      tmpNextNode = currentList1Node->next;
      insertNodeToEndList(&resultList, currentList1Node);
      currentList1Node = tmpNextNode;
    } else {
      tmpNextNode = currentList2Node->next;
      insertNodeToEndList(&resultList, currentList2Node);
      currentList2Node = tmpNextNode;
    }
  }

  while (currentList1Node != NULL) {
    list1NodeData = *(currentList1Node->dataPtr);
    tmpNextNode = currentList1Node->next;
    insertNodeToEndList(&resultList, currentList1Node);
    currentList1Node = tmpNextNode;
  }

  while (currentList2Node != NULL) {
    list2NodeData = *(currentList2Node->dataPtr);
    tmpNextNode = currentList2Node->next;
    insertNodeToEndList(&resultList, currentList2Node);
    currentList2Node = tmpNextNode;
  }

  return resultList;
}

void checkAllocation(void* ptr) {
  if (ptr == NULL) {
    exit(1);
  }
}

void printList(List* lst) {
  ListNode* curr = (*lst).head;

  while (curr != NULL) {
    printf("%d ", *(curr->dataPtr));
    curr = curr->next;
  }

  printf("\n");
}