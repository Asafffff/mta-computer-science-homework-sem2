#pragma once

#include "common.h"

Employee** extractEmployeesFromFile(Employee** extractedEmployees, char* fileName, int* numberOfEmployees);
float* extractPayRaisesFromFile(char* fileName, int numberOfEmployees);
void writeEmployeesToFile(Employee** employees, int numberOfEmployees, char* fileName);