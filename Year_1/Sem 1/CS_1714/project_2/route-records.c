#include"route-records.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

RouteRecord* createRecords(FILE* fileIn)
{
  int numRecords = 0;

  //infinite loop while !EOF
    //count lines
  while (!feof(fileIn))
  {
    char line[40];
    fgets(line, 39, fileIn);
    if (line[0] == '\n')
    {
      continue;
    }
    else
    {
      numRecords++;
    }
  }

  //decrements one for header line
  numRecords--;

  //allocate memory for records
  RouteRecord* records = (RouteRecord*)malloc(sizeof(RouteRecord) * numRecords);

  int i = 1;
  //for loop to go through the array using count and set passengers (all 6) equal to 0
  for (i = 0; i < numRecords; i++)
  {
    int j;
    for (j = 0; j < 6; j++)
    {
      records[i].passengers[j] = 0;
    }
  }

  //rewind the fileIn
  rewind(fileIn);

  //return the array
  return records;
}


int fillRecords(RouteRecord* r, FILE* fileIn)
{
  //Start final count int variable
  //int finalCount = 0;
  int curIdx = 0;
  //start temp variables to hold origin, destination, etc
  int tempMonth = 0;
  char tempOrigin[4];
  char tempDestination[4];
  char tempAirline[3];
  char passenger[10]; //useless
  int tempPassengers;
  //start a forever loop to read until !EOF
  char tmp[500];
  //Reads header line
  fgets(tmp, 499, fileIn);
  while (fgets(tmp, 499, fileIn) != NULL)
  {
    //printf("%d\n", curIdx);
    //scan from file into our temp variables
    //fscanf(fileIn, "%d,%[^,],%[^,],%[^,],%[^,],%d", &tempMonth, tempOrigin, tempDestination, tempAirline, passenger, &tempPassengers);
    //printf("%s\n\n", tmp);
    sscanf(tmp, "%d,%[^,],%[^,],%[^,],%[^,],%d", &tempMonth, tempOrigin, tempDestination, tempAirline, passenger, &tempPassengers);

    //call findAirlineRoute to see if we already have the flight within the malloc array
    //printf("\n\n\n");
    int index = findAirlineRoute(r, curIdx, tempOrigin, tempDestination, tempAirline, 0);
    if (index == -1)
    {
      //if we don't have the flight, we need to add it to the array
      // r[curIdx].origin = malloc(sizeof(char) * 4);
      // r[curIdx].destination = malloc(sizeof(char) * 4);
      // r[curIdx].airline = malloc(sizeof(char) * 3);
      // r[curIdx].passengers = malloc(sizeof(int) * 6);
      strcpy(r[curIdx].origin, tempOrigin);
      strcpy(r[curIdx].destination, tempDestination);
      strcpy(r[curIdx].airline, tempAirline);
      //printf("CurIndex: %d\nTempMonth: %d\n\n", curIdx, tempMonth);
      r[curIdx].passengers[tempMonth-1] = tempPassengers;
      ++curIdx;
    }
    else
    {
      //if we do have the flight, we need to add the passengers to the flight
      //printf("F\n");
      r[index].passengers[tempMonth-1] += tempPassengers;
      //++curIdx;
    }
  }
  rewind(fileIn);
  return curIdx;
}


int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int i)
{
  //Recursive
  if (i == length)
  {
    return -1;
  }
  //if the origin, destination, and airline match, return the index
  else if (strcmp(r[i].origin, origin) == 0 && strcmp(r[i].destination, destination) == 0 && strcmp(r[i].airline, airline) == 0)
  {
    return i;
  }
  else
  {
    return findAirlineRoute(r, length, origin, destination, airline, i+1);
  }
}


void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st)
{
  switch (st)
  {
    case ORIGIN:
      printf("Search by origin...\n");
      break;

    case ROUTE:
      printf("Search by route...\n");
      break;

    case AIRLINE:
      printf("Search by airline...\n");
      break;

    case DESTINATION:
      printf("Search by destination...\n");
      break;
  }
  //start int array for each month to hold total passengers
  int month[6] = {0,0,0,0,0,0};
  int numMatches = 0;
  //start a for loop to go through the array
  int i;
  for (i = 0; i < length; i++)
  {
    switch (st)
    {
      case ROUTE:
        if (strcmp(r[i].origin, key1) == 0 && strcmp(r[i].destination, key2) == 0)
        {
          printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
          numMatches++;
          int j;
          for (j = 0; j < 6; j++)
          {
            month[j] += r[i].passengers[j];
          }
        }
        break;

      case ORIGIN:
        if (strcmp(r[i].origin, key1) == 0)
        {
          printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
          numMatches++;
          int j;
          for (j = 0; j < 6; j++)
          {
            month[j] += r[i].passengers[j];
          }
        }
        break;

      case DESTINATION:
        if (strcmp(r[i].destination, key1) == 0)
        {
          printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
          numMatches++;
          int j;
          for (j = 0; j < 6; j++)
          {
            month[j] += r[i].passengers[j];
          }
        }
        break;

      case AIRLINE:
        if (strcmp(r[i].airline, key1) == 0)
        {
          printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
          numMatches++;
          int j;
          for (j = 0; j < 6; j++)
          {
            month[j] += r[i].passengers[j];
          }
        }
        break;
    }
  }
  printf("\n%d matches were found.\n",numMatches);
  printf("\nStatistics\nTotal Passengers:%22d\n",month[0]+month[1]+month[2]+month[3]+month[4]+month[5]);
  //Prints total passengers by month
  printf("Total Passengers in Month 1: %10d\n", month[0]);
  printf("Total Passengers in Month 2: %10d\n", month[1]);
  printf("Total Passengers in Month 3: %10d\n", month[2]);
  printf("Total Passengers in Month 4: %10d\n", month[3]);
  printf("Total Passengers in Month 5: %10d\n", month[4]);
  printf("Total Passengers in Month 6: %10d\n\n", month[5]);
  printf("Average Passengers per Month: %9d\n", (month[0]+month[1]+month[2]+month[3]+month[4]+month[5])/6);
}

void printMenu()
{
  printf("\n\n######### Airline Route Records Database MENU #########\n");
  printf("1. Search by Route\n");
  printf("2. Search by Origin Airport\n");
  printf("3. Search by Destination Airport\n");
  printf("4. Search by Airline\n");
  printf("5. Quit\n");
  printf("Enter your selection: ");
}
