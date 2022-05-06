#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* createSubExpressionByIndices(char* expression, int startIndex, int endIndex);
bool isValidInteger(char ch);
bool isValidOperator(char ch);
int findParentOperatorIndex(char* expression);
void checkAllocation(void* ptr);
void checkFile(FILE* file);
void sortLexicographically(char** strings, int numberOfStrings);