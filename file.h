#pragma once

#include "common.h"

char** readBinaryFileLowerChars(char* fileName, int numberOfStrings);
bool writeOutputToTxtFile(char** strings, int numberOfStrings, char* fileName);