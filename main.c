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
  int employeesArrLogSize = 0;
  int employeesArrPhySize = 1;
  Employee** extractedEmployees = (Employee**)malloc(sizeof(Employee*) * employeesArrPhySize);
  extractedEmployees = extractEmployeesFromFile(extractedEmployees, employeeFileName, &numberOfEmployees);
  float* extractedPayRaises = extractPayRaisesFromFile(payRaiseFileName, numberOfEmployees);

  // Add pay raises to employees
  for (int i = 0; i < numberOfEmployees; i++) {
    extractedEmployees[i]->salary += extractedPayRaises[i];
  }

  mergeSort(extractedEmployees, numberOfEmployees);
  writeEmployeesToFile(extractedEmployees, numberOfEmployees, employeeFileName);

  for (int i = 0; i < numberOfEmployees; i++) {
    free(extractedEmployees[i]->name);
    free(extractedEmployees[i]);
  }
  free(extractedEmployees);
  free(extractedPayRaises);

  return;
}