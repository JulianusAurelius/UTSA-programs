#ifndef ROUTERECORDS_H
#define ROUTERECORDS_H
#include<stdlib.h>
#include<stdio.h>

typedef enum SearchType { ROUTE, ORIGIN, DESTINATION, AIRLINE } SearchType;

typedef struct RouteRecord_struct {
  char origin[4];
  char destination[4];
  char airline[3];
  int passengers[6];
} RouteRecord;

//prototypes
RouteRecord* createRecords(FILE*);
int fillRecords(RouteRecord*, FILE*);
int findAirlineRoute(RouteRecord*, int, const char*, const char*, const char*, int);
void searchRecords(RouteRecord*, int, const char*, const char*, SearchType);
void printMenu();


#endif
