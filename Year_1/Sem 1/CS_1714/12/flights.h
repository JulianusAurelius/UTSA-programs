#include<stdio.h>
#include<stdlib.h>
#ifndef FLIGHTS_H
#define FLIGHTS_H
#define NUM_FLIGHTS 200

typedef struct Flight_Struct {
  char origin[4];
  char destination[4];
  char airline[3];
  int passengers;
} Flight;

#endif
