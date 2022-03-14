#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNINITIALIZED -1
#define COORDINATE_NOT_FOUND 1
#define COORDINATE_HAS_ANOTHER_OCCURRENCE 2
#define COORDINATE_X_WAS_UNIQUE 3
#define DEFAULT_COORDINATE_RESULT 0

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

int removeCoordinate(List* coord_list, int x, int y);
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

  // get the (x,y) to remove
  scanf("%d%d", &x, &y);
  res = removeCoordinate(&coordList, x, y);

  if (res == 1)
    printf("The point (%d,%d) didn't appear\n", x, y);
  else if (res == 2)
    printf("The point (%d,%d) has another occurrence\n", x, y);
  else if (res == 3)
    printf("The point (%d,%d) was the only point with this x\n", x, y);
  else
    printf("Other\n");
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

int removeCoordinate(List* coord_list, int x, int y) {
  XListNode *currX = (*coord_list).head, *prevX = NULL;
  YListNode *currY, *prevY = NULL;
  bool isCoordinateDeleted = false;

  while (currX != NULL) {
    if (currX->data == x) {
      currY = currX->yCoordinateList.head;
      while (currY != NULL) {
        if (currY->data == y && !isCoordinateDeleted) {
          if (prevY != NULL) {
            prevY->next = currY->next;
          } else {
            currX->yCoordinateList.head = currY->next;
          }
          isCoordinateDeleted = true;
        } else if (currY->data == y) {
          return COORDINATE_HAS_ANOTHER_OCCURRENCE;
        }

        prevY = currY;
        currY = currY->next;
      }
    }

    if (currX->yCoordinateList.head == NULL) {
      if (prevX != NULL) {
        prevX->next = currX->next;
      } else {
        (*coord_list).head = currX->next;
      }
      return COORDINATE_X_WAS_UNIQUE;
    }

    prevX = currX;
    currX = currX->next;
  }

  if (!isCoordinateDeleted) {
    return COORDINATE_NOT_FOUND;
  }

  return DEFAULT_COORDINATE_RESULT;
}