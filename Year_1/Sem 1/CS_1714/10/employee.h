#ifndef EMPLOYEE_H
#define EMPLOYEE_H

typedef struct Employee_Struct
{
    char name[10];
    int id;
    double salary;
} Employee;

Employee* readData(char*, int*);
Employee getBestEmployee(Employee[], int);
void writeData(char*, Employee);

#endif