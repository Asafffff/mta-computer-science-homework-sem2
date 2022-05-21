#ifndef _COMMON_H
#define _COMMON_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOT_FOUND -1
#define SHORT_ID_LENGTH 4
#define SHORT_PHONE_LENGTH 5
#define PHONE_NUMBER_DASH_INDEX 3

typedef unsigned char BYTE;

typedef struct _client {
  char id[9];     // “12345678”
  char phone[12]; // “054-1234567”
} Client;

typedef struct _short_client {
  unsigned char short_id[4];
  unsigned char short_phone[5];
} Short_client;

void checkAllocation(void* ptr);
void checkFile(FILE* file);
void* increaseArraySizeIfFull(void* arr, int* logSize, int* phySize, unsigned long sizeOfType);
Client* getClientByInput();
void normalizePhoneNumber(char* phoneNumber);
void denormalizePhoneNumber(char* phoneNumber);
BYTE* compressStringInteger(char* integerAsString, int numOfBytes);
BYTE* compressId(char* clientId);
BYTE* compressPhone(char* clientPhone);
Short_client* compressClients(Client clients[], int numOfClients);
Short_client* createShortClientArr(int numOfClients);
char* searchClientByID(Short_client* shortClients, int numOfClients, char* id);
int getClientIndexByCompressedId(Short_client* shortClients, int numOfClients, BYTE* compressedId);

#endif // _COMMON_H