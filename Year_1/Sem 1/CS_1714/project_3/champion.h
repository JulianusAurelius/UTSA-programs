#ifndef CHAMPION_H
#define CHAMPION_H
#include <stdio.h>
#include <stdlib.h>

// uses typedef so you don't need to have enum every time
typedef enum ChampionRole {
    MAGE,
    FIGHTER,
    SUPPORT,
    TANK
} ChampionRole;

// Champion struct with the internal members
typedef struct Champion
{
    ChampionRole role;
    int level;
    struct Champion* next;
} Champion;

// function prototypes
Champion* createChampion();
Champion* addChampion(Champion* head, Champion* champion);
Champion* buildChampionList(int n);
void printChampionList(Champion* head);
Champion* removeChampion(Champion* head);
Champion* destroyChampionList(Champion* head);

#endif