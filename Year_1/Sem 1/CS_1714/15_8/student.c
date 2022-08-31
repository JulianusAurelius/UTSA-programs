#include <stdio.h>
#include <stdlib.h>
#include "student.h"

void sortStudents(Student *students, int n)
{
    int i, j;
    Student temp;
    // Insertion sort
    for (i = 1; i < n; i++)
    {
        temp = students[i];
        for (j = i; j > 0 && students[j - 1].id > temp.id; j--)
        {
            students[j] = students[j - 1];
        }
        students[j] = temp;
    }
}

void print(Student *students, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("(%d,%s) -> ", students[i].id, students[i].name);
    }
    printf("\n");
}

Student searchStudent(Student *students, int n, int id)
{
    int i;
    // Binary search
    int low = 0;
    int high = n - 1;
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (students[mid].id == id)
        {
            return students[mid];
        }
        else if (students[mid].id < id)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return students[0];
}