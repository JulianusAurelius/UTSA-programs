#ifndef DICEGAME_C
#define DICEGAME_C
#include<stdio.h>
#include<stdlib.h>
#include"dicegame.h"

void printPlayerPoints(int p1, int p2)
{
  printf("P1      : %d\nP2      : %d\n\n", p1, p2);
}


int getRandomNumber(int min, int max)
{
  int range = max - min; //set the range of numbers (10,5 gives a range of 5)
  return ( (rand() % range) + min); //Modulos random by range, then adds min so the lowest value is min, and highest is max
}


enum ROUNDTYPE getRoundType()
{
  enum ROUNDTYPE round;
  int chance = getRandomNumber(1,10); //Random number used for probability
  if ( (chance >= 1) && (chance <= 2) ) //1-2 == 20% chance for BONUS
  {
    round = BONUS;
  }
  else if ( (chance >= 3) && (chance <= 5) ) //3-5 == 30% chance for DOUBLE
  {
    round = DOUBLE;
  }
  else //else, 6-10 == 50% chance for REGULAR
  {
    round = REGULAR;
  }
  return round;
}


int getRoundPoints(enum ROUNDTYPE t)
{
  int points = getRandomNumber(1,10) * 10; //Points are randomly generated generated from 1-10, then multiplied to 10-100 in multiples of 10
  switch (t) //Swtich statement based on ROUNDTYPE, which has default values for its declared types of int type 0, 1, and 2
  {
    case 0:
      points = 200; //BONUS is 200 points overall
      break;
    case 1:
      points *= 2; //DOUBLE is double the points
      break;
    case 2: //Considering removing this to shorten code, as it makes sense to include, but is otherwise not needed
      break; //REGULAR is normal, no change
  }
  return points;
}


void printRoundInfo(enum ROUNDTYPE t, int dice, int points)
{
  printf("TYPE    : "); //Sets up first line with Type and the proper spacing
  switch (t) //Switch case prints out proper round type based on logic presentend above in getRoundPoints
  {
    case 0:
      printf("BONUS\n");
      break;
    case 1:
      printf("DOUBLE\n");
      break;
    case 2:
      printf("REGULAR\n");
      break;
  }
  printf("DICE    : %d\n", dice);
  printf("POINTS  : %d\n", points);
}

#endif
