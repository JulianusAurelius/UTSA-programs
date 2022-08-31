#ifndef _road_h
#define _road_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "car.h"
#include "queue.h"
// #include "graph.h"

typedef struct RoadData
{
    /* TODO - Add data associated with road.  Suggested data: */
    /* length of this road */
    int length;

    /* information used to record/update whether the light at the end of this road is green or red */
    int light;
    int greenOnLength;
    int redOnLength;
    int currCycle;
    int reset;
    
    /* intersections this road starts from and moves to */
    // Vertex* start;
    // Vertex* end;
    int start;
    int end;

    /* array of cars associated with this road */
    Car** cars;

    /* queue of cars waiting to enter this road */
    Queue* addCarQueue;
    
}  RoadData;

void printCar();
RoadData* createRoad(int length, int start, int end);
int moveCar(RoadData* road1, RoadData* road2);
int addCar(RoadData* road);
void moveCars(RoadData* road, int* hasMoved);
int moveCarToFirst(RoadData* road1, RoadData* road2);
void freeRoad(RoadData* road);
void freeRoad(RoadData* road);
void printRoads(int time, RoadData** roadArray, int numRoads);

#endif

