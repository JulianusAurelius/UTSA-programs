#ifndef STUDENT_H
#define STUDENT_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Student_struct {
    int id;
    char name[11];
} Student;

void sortStudents(Student *students, int n);
void print(Student *students, int n);
Student searchStudent(Student *students, int n, int id);
#endif