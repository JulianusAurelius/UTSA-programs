#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef H
#define H

typedef struct ContactNode
{
   char contactName[50];
   char contactPhoneNum[50];
   struct ContactNode* nextNodePtr;
} ContactNode;

void CreateContactNode(ContactNode* thisNode, char nameInit[], char phoneNumInit[], ContactNode* nextLoc);
void InsertContactAfter(ContactNode* thisNode, ContactNode* newNode);
ContactNode* GetNextContact(ContactNode* thisNode);
void PrintContactNode(ContactNode* thisNode);
void rec(ContactNode* n);

#endif
