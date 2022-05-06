#pragma once

#include "common.h"

Employee** extractEmployeesFromFile(char* fileName, int* numberOfEmployees);
float* extractPayRaisesFromFile(char* fileName, int numberOfEmployees);
void writeEmployeesToFile(Employee** employees, int numberOfEmployees, char* fileName);