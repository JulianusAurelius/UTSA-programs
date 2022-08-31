#include <stdio.h>
#include<stdlib.h>
#include"employee.h"

int main()
{
    int size = 0;
    Employee* emp_p;
    Employee emp;
    emp_p = readData("a6-input.txt", &size);
    emp = getBestEmployee(emp_p, size);
    writeData("a6-output.txt", emp);
    
    free(emp_p);
    
    return 0;
}
