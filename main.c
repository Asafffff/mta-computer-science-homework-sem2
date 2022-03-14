#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_node {
  char* dataPtr;
  struct list_node* next;
} ListNode;

typedef struct list {
  ListNode* head;
  ListNode* tail;
} List;

typedef struct student {
  List first;
  int grade;
} Student;

// ----
void makeEmptyList(List* lst);
void insertDataToEndList(List* lst, char data);
void insertNodeToEndList(List* lst, ListNode* newTail);
ListNode* createNewListNode(char data, ListNode* next);
void checkAllocation(void* ptr);
// ----

Student unScramble(List lst);
bool isNodeDataANumber(ListNode* node);
bool isEmptyList(List lst);
ListNode* findNextApplicableNode(ListNode* node);
void printStudent(Student* student);
void freeList(List* lst);
int convertCharToInt(char c);

void main() {
  List lst;
  Student student;
  char ch;

  makeEmptyList(&lst);

  printf("Please enter the scrambled student:\n");

  ch = (char)getchar();
  while (ch != '\n') {
    insertDataToEndList(&lst, ch);
    ch = (char)getchar();
  }

  student = unScramble(lst);

  printStudent(&student);

  freeList(&student.first);
}

void makeEmptyList(List* lst) {
  lst->head = lst->tail = NULL;
}

ListNode* createNewListNode(char data, ListNode* next) {
  ListNode* result;

  result = (ListNode*)malloc(sizeof(ListNode));
  checkAllocation(result);

  result->dataPtr = (char*)malloc(sizeof(char));
  *(result->dataPtr) = data;
  result->next = next;

  return result;
}

void insertDataToEndList(List* lst, char data) {
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

bool isEmptyList(List lst) {
  return lst.head == NULL;
}

bool isNodeDataANumber(ListNode* node) {
  char ch = *(node->dataPtr);

  return (ch >= '0' && ch <= '9');
}

ListNode* findNextApplicableNode(ListNode* node) {
  while (node != NULL && !isNodeDataANumber(node)) {
    node = node->next;
  }

  return node;
}

Student unScramble(List lst) {
  ListNode* currentNode = lst.head;
  ListNode* prevNode = NULL;
  ListNode* nodeToRelease = NULL;
  bool isFirstNode = true;
  int grade = 0;

  while (currentNode != NULL) {
    if (isNodeDataANumber(currentNode)) {
      if (isFirstNode) {
        lst.head = currentNode->next;
      }

      grade *= 10;
      grade += convertCharToInt(*(currentNode->dataPtr));

      nodeToRelease = currentNode;
    } else {
      if (isFirstNode) {
        isFirstNode = false;
        prevNode = currentNode;
      } else {
        prevNode->next = currentNode;
        prevNode = currentNode;
      }
    }

    currentNode = currentNode->next;

    if (nodeToRelease != NULL) {
      free(nodeToRelease->dataPtr);
      free(nodeToRelease);
      nodeToRelease = NULL;
    }

    if (currentNode == NULL) {
      prevNode->next = NULL;
    }
  }

  lst.tail = prevNode;

  Student student = {.first = lst, .grade = grade};

  return student;
}

void checkAllocation(void* ptr) {
  if (ptr == NULL) {
    printf("Allocation error\n");
    exit(-1);
  }
}

void printStudent(Student* student) {
  printf("First name: ");
  ListNode* currentNode = student->first.head;
  while (currentNode != NULL) {
    printf("%c", *(currentNode->dataPtr));
    currentNode = currentNode->next;
  }
  printf("\n");
  printf("Grade: %d\n", student->grade);
}

void freeList(List* lst) {
  ListNode* currentNode = lst->head;
  ListNode* nextNode = NULL;

  while (currentNode != NULL) {
    nextNode = currentNode->next;
    free(currentNode->dataPtr);
    free(currentNode);
    currentNode = nextNode;
  }
}

int convertCharToInt(char c) {
  return c - '0';
}