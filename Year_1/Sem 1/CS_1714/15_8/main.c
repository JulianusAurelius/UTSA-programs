#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main(int argc, char *argv[])
{
    FILE* file = NULL;
    int count = 0;
    char tmp[100];
    int input;
    Student temp;
    int i;

    if (argc != 2)
    {
        printf("ERROR NO ARGS");
        exit(1);
    }
    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("ERROR FILE NOT OPEN");
        exit(1);
    }

    while (fgets(tmp, 100, file) != NULL)
    {
        ++count;
    }
    rewind(file);

    Student* students = (Student*)malloc(count * sizeof(Student));

    for (i = 0; i < count; ++i)
    {
        fscanf(file, "%d,", &students[i].id);
        fscanf(file, "%s", students[i].name);
    }

    print(students, count);
    sortStudents(students, count);
    print(students, count);

    scanf("%d", &input);
    temp = searchStudent(students, count, input);
    printf("(%d,%s)\n", temp.id, temp.name);



    return 0;
}