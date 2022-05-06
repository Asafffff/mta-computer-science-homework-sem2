#define _CRT_SECURE_NO_WARNINGS
#include "common.h"
#include "file.h"

void main(int argc, char** argv) {
  if (argc != 3) {
    printf("Invalid number of arguments.\nExiting...");
    exit(1);
  }

  char* employeeFileName = argv[1];
  char* payRaiseFileName = argv[2];

  int numberOfEmployees;
  Employee** extractedEmployees = extractEmployeesFromFile(employeeFileName, &numberOfEmployees);
  float* extractedPayRaises = extractPayRaisesFromFile(payRaiseFileName, numberOfEmployees);

  // Add pay raises to employees
  for (int i = 0; i < numberOfEmployees; i++) {
    extractedEmployees[i]->salary += extractedPayRaises[i];
  }

  quicksort(extractedEmployees, numberOfEmployees);
  writeEmployeesToFile(extractedEmployees, numberOfEmployees, employeeFileName);

  return;
}