#ifndef ITEM_C
#define ITEM_C
#include<stdio.h>
#include<stdlib.h>
#include"ItemToPurchase.h"

void MakeItemBlank(ItemToPurchase* i)
{
  strcpy(i->itemName, "none");
  i->itemPrice = 0;
  i->itemQuantity = 0;
}

void PrintItemCost(ItemToPurchase i)
{

}

#endif
