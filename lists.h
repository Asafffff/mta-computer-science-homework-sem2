#pragma once
#include "common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode {
  int data;
  struct listNode* next;
} ListNode;

typedef struct list {
  ListNode* head;
  ListNode* tail;
} List;

ListNode* createListNode(int data, ListNode* next);
void insertDataToStartOfList(List* list, int data);
void insertDataToEndOfList(List* list, int data);
void insertNodeToStartOfList(List* list, ListNode* node);
void insertNodeToEndOfList(List* list, ListNode* node);
void initEmptyList(List* list);
void freeListRec(ListNode* listNode);
void printLeafListRec(ListNode* listNode);
bool replaceListNodeInLeafListRec(ListNode* listNode, int prevNodeData, int newNodeData);
