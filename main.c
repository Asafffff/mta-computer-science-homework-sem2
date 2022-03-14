#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNINITIALIZED -1

typedef struct YlistNode {
  int data;
  struct YlistNode* next;
} YListNode;

typedef struct Ylist {
  YListNode* head;
  YListNode* tail;
} YList;

typedef struct XlistNode {
  int data;
  struct XlistNode* next;
  struct XlistNode* prev;
  YList yCoordinateList;
} XListNode;

typedef struct list {
  XListNode* head;
  XListNode* tail;
} List;

int insertCoordinate(List* coord_list, int x, int y);
void printList(List* lst);
List getCoordList();

// --------------------------------------------------
void freeList(List* lst);
void freeListY(YList* lst);
void makeEmptyList(List* lst);
void makeEmptyListY(YList* lst);
bool isEmptyList(List lst);
bool isEmptyListY(YList lst);
XListNode* createNewListNode(int data, XListNode* next);
YListNode* createNewListNodeY(int data, YListNode* next);
void insertDataToEndList(List* lst, int data);
void insertDataToEndListY(YList* lst, int data);
void insertNodeToEndList(List* lst, XListNode* newTail);
void insertNodeToEndListY(YList* lst, YListNode* newTail);
void checkAllocation(void* ptr);
// --------------------------------------------------

void main() {
  List coordList;
  int x, y;
  int res;
  coordList = getCoordList();

  // get the (x,y) to insert
  scanf("%d%d", &x, &y);
  res = insertCoordinate(&coordList, x, y);

  if (res == 0)
    printf("The point (%d,%d) didn't appear\n", x, y);
  else
    printf("The point (%d,%d) already appeared\n", x, y);

  printf("Updated list: ");
  printList(&coordList);
  freeList(&coordList);
}

void makeEmptyList(List* lst) {
  lst->head = lst->tail = NULL;
}

void makeEmptyListY(YList* lst) {
  lst->head = lst->tail = NULL;
}

XListNode* createNewListNode(int data, XListNode* next) {
  XListNode* result;

  result = (XListNode*)malloc(sizeof(XListNode));
  checkAllocation(result);

  result->data = data;
  result->next = next;

  return result;
}

YListNode* createNewListNodeY(int data, YListNode* next) {
  YListNode* result;

  result = (YListNode*)malloc(sizeof(YListNode));
  checkAllocation(result);

  result->data = data;
  result->next = next;

  return result;
}

void insertDataToEndList(List* lst, int data) {
  XListNode* result = createNewListNode(data, NULL);

  insertNodeToEndList(lst, result);
}

void insertDataToEndListY(YList* lst, int data) {
  YListNode* result = createNewListNodeY(data, NULL);

  insertNodeToEndListY(lst, result);
}

void insertNodeToEndList(List* lst, XListNode* newTail) {
  XListNode* prevTail = lst->tail;
  newTail->next = NULL;
  newTail->prev = prevTail;

  if (isEmptyList(*lst))
    lst->head = lst->tail = newTail;
  else {
    lst->tail->next = newTail;
    lst->tail = newTail;
  }
}

void insertNodeToEndListY(YList* lst, YListNode* newTail) {
  newTail->next = NULL;

  if (isEmptyListY(*lst))
    lst->head = lst->tail = newTail;
  else {
    lst->tail->next = newTail;
    lst->tail = newTail;
  }
}

void freeList(List* lst) {
  XListNode *curr = (*lst).head, *next;

  while (curr != NULL) {
    next = curr->next;
    freeListY(&(curr->yCoordinateList));
    free(curr);
    curr = next;
  }
}

void freeListY(YList* lst) {
  YListNode *curr = (*lst).head, *next;

  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }
}

bool isEmptyList(List lst) {
  return lst.head == NULL;
}

bool isEmptyListY(YList lst) {
  return lst.head == NULL;
}

void checkAllocation(void* ptr) {
  if (ptr == NULL) {
    exit(1);
  }
}

void printList(List* lst) {
  XListNode* currX = (*lst).head;

  while (currX != NULL) {
    YListNode* currY = currX->yCoordinateList.head;
    while (currY != NULL) {
      printf("(%d,%d)", currX->data, currY->data);

      if (currY->next != NULL) {
        printf(", ");
      }

      currY = currY->next;
    }

    if (currX->next != NULL) {
      printf(", ");
    }

    currX = currX->next;
  }

  printf("\n");
}

List getCoordList() {
  int numberOfPoints, i, x, y;
  int lastX = UNINITIALIZED;

  scanf(" %d", &numberOfPoints);

  List xCoordList;
  makeEmptyList(&xCoordList);

  for (i = 0; i < numberOfPoints; i++) {
    scanf(" %d %d", &x, &y);

    if (lastX != x) {
      insertDataToEndList(&xCoordList, x);
      makeEmptyListY(&(xCoordList.tail->yCoordinateList));
      lastX = x;
    }
    YListNode* currentYNode = createNewListNodeY(y, NULL);
    insertNodeToEndListY(&(xCoordList.tail->yCoordinateList), currentYNode);
  }

  return xCoordList;
}

int insertCoordinate(List* coord_list, int x, int y) {
  XListNode* prevX;
  XListNode* currX = (*coord_list).head;
  bool isAlreadyExist = false, isInserted = false;

  while (currX != NULL && !isAlreadyExist) {
    if (currX->data == x) {
      YListNode* prevY;
      YListNode* currY = currX->yCoordinateList.head;
      while (currY != NULL && !isAlreadyExist) {
        if (currY->data == y) {
          isAlreadyExist = true;
        }

        prevY = currY;
        currY = currY->next;
      }

      YListNode* newYNode = createNewListNodeY(y, NULL);
      insertNodeToEndListY(&(currX->yCoordinateList), newYNode);
      isInserted = true;
    }

    currX = currX->next;
  }

  if (!isInserted) {
    XListNode* newXNode = createNewListNode(x, NULL);
    YListNode* newYNode = createNewListNodeY(y, NULL);
    insertNodeToEndList(coord_list, newXNode);
    makeEmptyListY(&(*coord_list).tail->yCoordinateList);
    insertNodeToEndListY(&(newXNode->yCoordinateList), newYNode);
  }

  return (int)isAlreadyExist;
}