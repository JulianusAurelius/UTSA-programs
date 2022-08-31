#ifndef ITEM_H
#define ITEM_H
#include<stdio.h>
#include<stdlib.h>

typedef struct ItemToPurchase_Struct {
  char itemName[];
  int itemPrice;
  int itemQuantity;
} ItemToPurchase;

void MakeItemBlank(ItemToPurchase*);
void PrintItemCost(ItemToPurchase);

#endif
