#include "common.h"

void checkAllocation(void* ptr) {
  if (ptr == NULL) {
    exit(1);
  }
}

void checkFile(FILE* file) {
  if (file == NULL) {
    printf("Could not open file.\nExiting...");
    exit(1);
  }
}

/**
 * @brief Increases the size of the array, if it is full
 *
 * @param arr The array to be resized
 * @param logSize The logical size of the array
 * @param phySize The physical size of the array
 * @return void* The resized array, before casting to the original type
 */
void* increaseArraySizeIfFull(void* arr, int* logSize, int* phySize, unsigned long sizeOfType) {
  if (*logSize == *phySize) {
    (*phySize) *= 2;
    arr = realloc(arr, (*phySize) * sizeOfType);
    checkAllocation(arr);
  }

  return arr;
}

Client* getClientByInput() {
  Client* client = malloc(sizeof(Client));
  checkAllocation(client);

  printf("Enter client id: ");
  scanf("%s", client->id);

  printf("Enter client phone (including '-'): ");
  scanf("%s", client->phone);

  return client;
}

BYTE* compressId(char* clientId) {
  int i;
  BYTE* compressedId = malloc(sizeof(BYTE) * SHORT_ID_LENGTH);
  BYTE currentByte = 0x00;
  checkAllocation(compressedId);

  int clientIdLength = strlen(clientId);

  for (i = 0; i < clientIdLength; i++) {
    char currentDigit = clientId[i] - '0';

    // If the index is even, it should take the 4 leftmost bits
    if (i % 2 == 0) {
      currentByte |= currentDigit << 4;
    } else {
      currentByte |= currentDigit;

      // Append to compressedId and reset state
      compressedId[i / 2] = currentByte;
      currentByte = 0x00;
    }
  }

  return compressedId;
}

void normalizePhone(char* phoneNumber) {
  int i;
  int phoneNumberLength = strlen(phoneNumber);

  for (i = 3; i < phoneNumberLength; i++) {
    phoneNumber[i] = phoneNumber[i + 1];
  }

  return;
}

BYTE* compressPhone(char* clientPhoneNumber) {
  int i;

  BYTE* compressedPhone = malloc(sizeof(BYTE) * SHORT_PHONE_LENGTH);
  BYTE currentByte = 0x00;
  checkAllocation(compressedPhone);

  normalizePhone(clientPhoneNumber);
  int clientPhoneLength = strlen(clientPhoneNumber);

  for (i = 0; i < clientPhoneLength; i++) {
    char currentDigit = clientPhoneNumber[i] - '0';

    // If the index is even, it should take the 4 leftmost bits
    if (i % 2 == 0) {
      currentByte |= currentDigit << 4;
    } else {
      currentByte |= currentDigit;

      // Append to compressedId and reset state
      compressedPhone[i / 2] = currentByte;
      currentByte = 0x00;
    }
  }

  return compressedPhone;
}

Short_client* compressClients(Client* clients, int numOfClients) {
  int i;

  Short_client* shortClients = (Short_client*)malloc(sizeof(Short_client) * numOfClients);
  checkAllocation(shortClients);

  for (i = 0; i < numOfClients; i++) {
    BYTE* compressedId = compressId(clients[i].id);
    BYTE* compressedPhone = compressPhone(clients[i].phone);
    memcpy(shortClients[i].short_id, compressedId, sizeof(BYTE) * SHORT_ID_LENGTH);
    memcpy(shortClients[i].short_phone, compressedPhone, sizeof(BYTE) * SHORT_PHONE_LENGTH);
  }

  return shortClients;
};

Short_client* createShortClientArr(int numOfClients) {
  int i;
  Client* clients = (Client*)malloc(sizeof(Client) * numOfClients);
  checkAllocation(clients);

  for (i = 0; i < numOfClients; i++) {
    Client* newClient = getClientByInput();
    clients[i] = *newClient;
    free(newClient);
  }

  Short_client* shortClients = compressClients(clients, numOfClients);
  free(clients);

  return shortClients;
}

char* searchClientByID(Short_client* shortClients, int numOfClients, char* id) {}