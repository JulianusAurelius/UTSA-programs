#ifndef EMPLOYEE_C
#define EMPLOYEE_C
#include<stdio.h>
#include<stdlib.h>
#include"employee.h"

Employee* readData(char* filen, int* count)
{
    Employee* p;
    FILE* file;
    file = fopen(filen, "r");
    
    char line[100];
    
    while(!feof(file))
    {
        fgets(line, 99, file);
        ++*count;
    }
    //printf("Employee.c line count: %d\n", *count);
    fclose(file);
    
    p = (Employee*)malloc(sizeof(Employee) * (*count));
    
    file = fopen(filen, "r");
    for (int i = 0; i < (*count); ++i) 
    {
        fscanf(file, "%s ", ((p+i)->name));
        fscanf(file, "%d ", &((p+i)->id));
        fscanf(file, "%lf ", &((p+i)->salary));
    }
    fclose(file);
    
    return p;
}

Employee getBestEmployee(Employee* arr, int size)
{
    int max_i = 0;
    double max_s = arr[0].salary;
    for (int i = 0; i < size; ++i)
    {
        if ( arr[i].salary > max_s )
        {
            max_i = i;
            max_s = arr[i].salary;
        }
    }
    return arr[max_i];
}

void writeData(char* filen, Employee emp)
{
    FILE* file;
    file = fopen(filen, "w");
    fprintf(file, "%s %d %.0lf\n", emp.name, emp.id, emp.salary);
    fclose(file);
    // printf("%s %d %.0lf\n", emp.name, emp.id, emp.salary);
    
}

#endif