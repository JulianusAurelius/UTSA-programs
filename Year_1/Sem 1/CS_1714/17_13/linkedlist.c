#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"linkedlist.h"

LLNode* createNode(int id, char name[10], double gpa)
{
    LLNode *newNode = (LLNode*)malloc(sizeof(LLNode));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->gpa = gpa;
    newNode->next = NULL;
    return newNode;
}

LLNode* insertNode(LLNode *head, LLNode *newNode)
{
    LLNode *curr = head;
    LLNode *prev = NULL;
    while(curr != NULL && strcmp(curr->name, newNode->name) < 0)
    {
        prev = curr;
        curr = curr->next;
    }
    if(prev == NULL)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        prev->next = newNode;
        newNode->next = curr;
    }
    return head;
}

double averageGPA(LLNode *head)
{
    LLNode *curr = head;
    double sum = 0;
    int count = 0;
    while(curr != NULL)
    {
        sum += curr->gpa;
        count++;
        curr = curr->next;
    }
    return sum/count;
}

void printLL(LLNode *head)
{
    if (head != NULL)
    {
        printf("(%d,%s,%.2lf) -> ", head->id, head->name, head->gpa);
        printLL(head->next);
    }
}

LLNode* destroyLL(LLNode *head)
{
    LLNode *curr = head;
    LLNode *next;
    while(curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    return NULL;
}