#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"flights.h"

int main(int argc, char* argv[])
{
  if (!(argc >= 2))
  {
    printf("ERROR NO ARGS");
    return 1;
  }

  FILE* file = NULL;
  file = fopen(argv[1], "r");
  if (file == NULL)
  {
    printf("ERROR FILE NOT OPEN");
    return 1;
  }

  Flight* flights = (Flight*)malloc(sizeof(Flight)*NUM_FLIGHTS);
  int num;
  for (int i = 0; i < NUM_FLIGHTS; ++i)
  {
    num = fscanf(file, "%[^,],%[^,],%[^,],%d", flights[i].origin, flights[i].destination, flights[i].airline, &flights[i].passengers);
    // if (num != 4)
    // {
    //   printf("Not 200\n");
    //   break;
    // }
  }

  char in[3];
  printf("Enter 2 letter airline code ");
  fgets(in, 3, stdin);
  printf("\n");
  in[3] = '\0';

  int num_f = 0;
  int num_p = 0;
  for (int i = 0; i < NUM_FLIGHTS; ++i)
  {
    if ( strcmp(flights[i].airline, in) == 0)
    {
      ++num_f;
      num_p += flights[i].passengers;
    }
  }

  printf("airline: %s\nflights: %d\npassengers: %d\n", in, num_f, num_p);

  fclose(file);
  free(flights);
}
