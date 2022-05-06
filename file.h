#pragma once

#include "common.h"

STUDENT** extractStudentsFromFile(char* fileName, int* numberOfStudents);
void writeStudentsOffsetsToFile(STUDENT** students, int numberOfStudents, char* fileName);
char** findAverageGrade(char* fileName, int minAverage, int* resSize);
void freeArrayOfStudents(STUDENT** extractedStudents, int extractedStudentsCount);