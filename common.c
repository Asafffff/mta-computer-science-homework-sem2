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

BYTE* compressStringInteger(char* integerAsString, int numOfBytes) {
  int i;
  BYTE* compressedString = (BYTE*)malloc(sizeof(BYTE) * numOfBytes);
  checkAllocation(compressedString);

  int stringLength = strlen(integerAsString);
  BYTE currentByte = 0x00;

  for (i = 0; i < stringLength; i++) {
    char currentDigit = integerAsString[i] - '0';

    // If the index is even, it should take the 4 leftmost bits
    if (i % 2 == 0) {
      currentByte |= currentDigit << 4;
    } else {
      currentByte |= currentDigit;

      // Append to compressedId and reset state
      compressedString[i / 2] = currentByte;
      currentByte = 0x00;
    }
  }

  return compressedString;
}

void normalizePhoneNumber(char* phoneNumber) {
  int i;
  int phoneNumberLength = strlen(phoneNumber);

  for (i = PHONE_NUMBER_DASH_INDEX; i < phoneNumberLength; i++) {
    phoneNumber[i] = phoneNumber[i + 1];
  }

  return;
}

void denormalizePhoneNumber(char* phoneNumber) {
  int i;
  int phoneNumberLength = strlen(phoneNumber);

  for (i = phoneNumberLength; i > PHONE_NUMBER_DASH_INDEX; i--) {
    phoneNumber[i] = phoneNumber[i - 1];
  }

  phoneNumber[PHONE_NUMBER_DASH_INDEX] = '-';

  return;
}

BYTE* compressId(char* clientId) {
  BYTE* compressedId = compressStringInteger(clientId, SHORT_ID_LENGTH);

  return compressedId;
}

BYTE* compressPhone(char* clientPhoneNumber) {
  normalizePhoneNumber(clientPhoneNumber);
  BYTE* compressedPhone = compressStringInteger(clientPhoneNumber, SHORT_PHONE_LENGTH);

  return compressedPhone;
}

char* uncompressPhone(BYTE* compressedPhoneNumber) {
  int i;
  char* phoneNumber = (char*)calloc(SHORT_PHONE_LENGTH * 2 + 1 + 1,
                                    sizeof(char)); // +1 for the upcoming '-' char, +1 for the null terminator
  checkAllocation(phoneNumber);

  BYTE firstNumMask = 0xF0;
  BYTE secondNumMask = 0x0F;

  for (i = 0; i < SHORT_PHONE_LENGTH; i++) {
    phoneNumber[2 * i] = ((compressedPhoneNumber[i] & firstNumMask) >> 4) + '0';
    phoneNumber[2 * i + 1] = ((compressedPhoneNumber[i] & secondNumMask)) + '0';
  }

  return phoneNumber;
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

int getClientIndexByCompressedId(Short_client* shortClients, int numOfClients, BYTE* compressedId) {
  int i, j;

  int clientIndex = NOT_FOUND;

  for (i = 0; i < numOfClients; i++) {
    Short_client currentClient = shortClients[i];

    for (j = 0; j < SHORT_ID_LENGTH; j++) {
      BYTE clientShortIdByte = currentClient.short_id[j];
      BYTE searchShortIdByte = compressedId[j];
      if (currentClient.short_id[j] != compressedId[j]) {
        break;
      }

      if (j == SHORT_ID_LENGTH - 1) {
        clientIndex = i;
      }
    }

    if (clientIndex != NOT_FOUND) {
      break;
    }
  }

  return clientIndex;
}

char* searchClientByID(Short_client* shortClients, int numOfClients, char* id) {
  BYTE* compressedId = compressId(id);

  int clientIndex = getClientIndexByCompressedId(shortClients, numOfClients, compressedId);

  if (clientIndex == NOT_FOUND) {
    return NULL;
  }

  char* uncompressedPhoneNumber = uncompressPhone(shortClients[clientIndex].short_phone);
  denormalizePhoneNumber(uncompressedPhoneNumber);

  return uncompressedPhoneNumber;
}