#include "file.h"

/**
 * @brief Reads a binary file and extracts the lowercase characters.
 *
 * @param fileName The name of the file to read.
 * @param numberOfStrings The number of strings to extract.
 * @return char** The extracted strings.
 */
char** readBinaryFileLowerChars(char* fileName, int numberOfStrings) {
  int currentStringSize = 0;

  FILE* binaryFile = fopen(fileName, "rb");
  checkFile(binaryFile);
  char** extractedStrings = (char**)malloc(sizeof(char*) * numberOfStrings);
  char* currentWord;

  for (int i = 0; i < numberOfStrings; i++) {
    fread(&currentStringSize, sizeof(int), 1, binaryFile);
    int currentWordWriteIndex = 0;
    currentWord = (char*)malloc(sizeof(char) * currentStringSize + 1); // +1 for null terminator
    checkAllocation(currentWord);

    for (int j = 0; j < currentStringSize; j++) {
      char currentChar = fgetc(binaryFile);

      if (currentChar >= 'a' && currentChar <= 'z') {
        currentWord[currentWordWriteIndex] = currentChar;
        currentWordWriteIndex++;
      }
    }
    currentWord[currentWordWriteIndex] = '\0';

    currentWord = (char*)realloc(currentWord, strlen(currentWord) * sizeof(char) + 1); // +1 for null terminator
    checkAllocation(currentWord);

    extractedStrings[i] = currentWord;
  }

  return extractedStrings;
}

/**
 * @brief Write the strings to a text file.
 *
 * @param strings The strings to write.
 * @param numberOfStrings The number of strings.
 * @param fileName The name of the file to write to.
 * @return true
 * @return false
 */
bool writeOutputToTxtFile(char** strings, int numberOfStrings, char* fileName) {
  FILE* outputFile = fopen(fileName, "w");
  checkFile(outputFile);

  for (int i = 0; i < numberOfStrings; i++) {
    fprintf(outputFile, "%s", strings[i]);

    if (i != numberOfStrings - 1) {
      fprintf(outputFile, "\n");
    }
  }

  return true;
}