#ifndef DICEGAME_H
#define DICEGAME_H
#include<stdio.h>
#include<stdlib.h>

enum ROUNDTYPE {BONUS, DOUBLE, REGULAR};

void printPlayerPoints(int, int);
int getRandomNumber(int, int);
enum ROUNDTYPE getRoundType();
int getRoundPoints(enum ROUNDTYPE);
void printRoundInfo(enum ROUNDTYPE, int, int);

#endif
