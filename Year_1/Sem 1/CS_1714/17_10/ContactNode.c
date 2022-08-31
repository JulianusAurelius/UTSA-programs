#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "ContactNode.h"

void CreateContactNode(ContactNode* thisNode, char nameInit[], char phoneNumInit[], ContactNode* nextLoc)
{
   strcpy(thisNode->contactName, nameInit);
   strcpy(thisNode->contactPhoneNum, phoneNumInit);
   thisNode->nextNodePtr = nextLoc;
}

void InsertContactAfter(ContactNode* thisNode, ContactNode* newNode)
{
   newNode->nextNodePtr = thisNode->nextNodePtr;
   thisNode->nextNodePtr = newNode;
}

ContactNode* GetNextContact(ContactNode* thisNode)
{
   return thisNode->nextNodePtr;
}

void PrintContactNode(ContactNode* thisNode)
{
   printf("Name: %s\nPhone number: %s\n\n", thisNode->contactName, thisNode->contactPhoneNum);
}

void rec(ContactNode* n)
{
   if (n != NULL)
   {
      PrintContactNode(n);
      rec(GetNextContact(n));
   }
}
