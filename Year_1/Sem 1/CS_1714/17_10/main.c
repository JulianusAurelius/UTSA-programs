#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "ContactNode.h"

int main(void)
{

   ContactNode* x;
   x = (ContactNode*)malloc(sizeof(ContactNode));
   char contactName[50];
   char contactPhoneNum[50];
   printf("Person 1\nEnter name:");
   fgets(contactName, 49, stdin);
   contactName[strlen(contactName)-1] = '\0';
   printf("\nEnter phone number:");
   scanf("%s\n", contactPhoneNum);
   printf("\nYou entered: %s, %s\n", contactName, contactPhoneNum);
   CreateContactNode(x, contactName, contactPhoneNum, NULL);
   printf("\nPerson 2\nEnter name:");
   fgets(contactName, 49, stdin);
   contactName[strlen(contactName)-1] = '\0';
   printf("\nEnter phone number:");
   scanf("%s\n", contactPhoneNum);
   printf("\nYou entered: %s, %s\n", contactName, contactPhoneNum);
   x->nextNodePtr = (ContactNode*)malloc(sizeof(ContactNode));
   CreateContactNode(x->nextNodePtr, contactName, contactPhoneNum, NULL);
   printf("\nPerson 3\nEnter name:");
   fgets(contactName, 49, stdin);
   contactName[strlen(contactName)-1] = '\0';
   printf("\nEnter phone number:");
   scanf("%s\n", contactPhoneNum);
   printf("\nYou entered: %s, %s\n", contactName, contactPhoneNum);
   x->nextNodePtr->nextNodePtr = (ContactNode*)malloc(sizeof(ContactNode));
   CreateContactNode(x->nextNodePtr->nextNodePtr, contactName, contactPhoneNum, NULL);
   printf("\n");
   
   printf("CONTACT LIST\n");
   rec(x);
   
   
  
   return 0;
}
