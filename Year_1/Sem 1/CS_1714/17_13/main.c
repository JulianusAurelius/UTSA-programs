#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"linkedlist.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("ERROR NO ARGS");
        return 1;
    }
    FILE* f = NULL;
    f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("ERROR FILE NOT OPEN");
        return 1;
    }
    LLNode *head = NULL;
    LLNode *newNode = NULL;
    char name[10];
    int id;
    double gpa;
    int num;
    num = fscanf(f, "%d,%[^,],%lf\n", &id, name, &gpa);
    while(num == 3)
    {
        
        // printf("%s", name);
        newNode = createNode(id, name, gpa);
        head = insertNode(head, newNode);
        num = fscanf(f, "%d,%[^,],%lf\n", &id, name, &gpa);
    }

    fclose(f);
    printf("Average = %.2lf\n", averageGPA(head));
    printLL(head);
    printf("\n");
    destroyLL(head);
    return 0;
}