#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNINITIALIZED_VALUE 0

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

List getList();
List merge(List lst1, List lst2);
void mergeRec(ListNode* list1Node, ListNode* list2Node, List* mergedList);
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

void mergeRec(ListNode* list1Node, ListNode* list2Node, List* mergedList) {
  int list1NodeData, list2NodeData;
  ListNode* tmpNextNode = NULL;

  list1NodeData = list2NodeData = UNINITIALIZED_VALUE;

  if (list1Node == NULL || list2Node == NULL) {
    if (list1Node == NULL && list2Node == NULL) {
      return;
    } else if (list1Node == NULL) {
      tmpNextNode = list2Node->next;
      insertNodeToEndList(mergedList, list2Node);
      mergeRec(NULL, tmpNextNode, mergedList);
      return;
    } else {
      tmpNextNode = list1Node->next;
      insertNodeToEndList(mergedList, list1Node);
      mergeRec(tmpNextNode, NULL, mergedList);
      return;
    }
  }

  list1NodeData = *(list1Node->dataPtr);
  list2NodeData = *(list2Node->dataPtr);

  if (list1NodeData > list2NodeData) {
    tmpNextNode = list1Node->next;
    insertNodeToEndList(mergedList, list1Node);
    mergeRec(tmpNextNode, list2Node, mergedList);
  } else {
    tmpNextNode = list2Node->next;
    insertNodeToEndList(mergedList, list2Node);
    mergeRec(list1Node, tmpNextNode, mergedList);
  }
}

List merge(List lst1, List lst2) {
  List resultList;
  makeEmptyList(&resultList);

  mergeRec(lst1.head, lst2.head, &resultList);

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