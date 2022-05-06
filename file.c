#include "file.h"

/**
 * @brief Extracts employees from file.
 *
 * @param fileName Name of file to extract from.
 * @param numberOfEmployees (Output Param) Pointer to number of employees in file.
 * @return Employee** Array of employees.
 */
Employee** extractEmployeesFromFile(char* fileName, int* numberOfEmployees) {
  FILE* binaryFile = fopen(fileName, "rb");
  checkFile(binaryFile);
  int employeesArrLogSize = 0;
  int employeesArrPhySize = 1;
  Employee** extractedEmployees = (Employee**)malloc(sizeof(Employee*) * employeesArrPhySize);

  while (true) {
    Employee* employee = (Employee*)malloc(sizeof(Employee));
    fread(&employee->name_length, sizeof(int), 1, binaryFile);

    if (employee->name_length == 0) {
      free(employee);
      break;
    }

    employee->name = (char*)malloc(sizeof(char) * employee->name_length + 1); // +1 for null terminator

    fread(employee->name, sizeof(char), employee->name_length, binaryFile);
    employee->name[employee->name_length] = '\0';

    fread(&employee->salary, sizeof(float), 1, binaryFile);

    if (employeesArrLogSize == employeesArrPhySize) {
      employeesArrPhySize *= 2;
      extractedEmployees = (Employee**)realloc(extractedEmployees, sizeof(Employee*) * employeesArrPhySize);
    }

    extractedEmployees[employeesArrLogSize] = employee;
    employeesArrLogSize++;
  }

  fclose(binaryFile);

  extractedEmployees = (Employee**)realloc(extractedEmployees, sizeof(Employee*) * employeesArrLogSize);
  employeesArrPhySize = employeesArrLogSize;

  *numberOfEmployees = employeesArrLogSize;
  return extractedEmployees;
}

/**
 * @brief Extracts pay raises from file.
 *
 * @param fileName Name of file to extract from.
 * @param numberOfEmployees Number of employees in file.
 * @return float* Array of pay raises.
 */
float* extractPayRaisesFromFile(char* fileName, int numberOfEmployees) {

  FILE* binaryFile = fopen(fileName, "rb");
  checkFile(binaryFile);
  float* extractedPayRaises = (float*)malloc(sizeof(float) * numberOfEmployees);

  for (int i = 0; i < numberOfEmployees; i++) {
    fread(&extractedPayRaises[i], sizeof(float), 1, binaryFile);
  }

  fclose(binaryFile);

  return extractedPayRaises;
}

/**
 * @brief Writes employees to file.
 *
 * @param employees Array of employees.
 * @param numberOfEmployees Number of employees in array.
 * @param fileName Name of file to write to.
 */
void writeEmployeesToFile(Employee** employees, int numberOfEmployees, char* fileName) {
  FILE* outputFile = fopen(fileName, "wb");
  checkFile(outputFile);

  for (int i = 0; i < numberOfEmployees; i++) {
    fwrite(&employees[i]->name_length, sizeof(int), 1, outputFile);
    fwrite(employees[i]->name, sizeof(char), employees[i]->name_length, outputFile);
    fwrite(&employees[i]->salary, sizeof(float), 1, outputFile);
  }

  fclose(outputFile);

  return;
}