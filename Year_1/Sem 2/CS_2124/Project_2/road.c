#include "road.h"

/* Suggested TODO - Write a function to create road.
 */
RoadData* createRoad(int length, int start, int end)
{
    RoadData* road = malloc(sizeof(RoadData));
    road->length = length;
    road->start = start;
    road->end = end;
    road->light = 0;
    road->cars = malloc(sizeof(Car*) * length);
    //set all cars to NULL
    int i;
    for(i = 0; i < length; i++)
    {
        road->cars[i] = NULL;
    }
    road->addCarQueue = createQueue();
    return road;
}

/* Suggested TODO - Write a function to free a road.
 */
void freeRoad(RoadData* road)
{
    // free car array on the road
    // int j;
    // for (j = 0; j < trafficData->roadArray[i]->length; j++)
    // {
    //     free(trafficData->roadArray[i]->cars[j]);
    // }
    // free(trafficData->roadArray[i]->cars);
    // freeQueue(trafficData->roadArray[i]->addCarQueue);
    // free(trafficData->roadArray[i]);
    if (!isEmpty(road->addCarQueue))
    {
        freeQueue(road->addCarQueue);
    }
    freeQueue(road->addCarQueue);
    int i = 0;
    for (i = 0; i < road->length; i++)
    {
        if (road->cars[i] != NULL)
        {
            free(road->cars[i]);
        }
    }
    free(road->cars);
    free(road);
}

/* Suggested TODO - Write a function that attempts to move the cars on a given road forward (if space ahead of them was empty).
 */
void moveCars(RoadData* road, int* hasMoved)
{
    int end = road->length - 1;
    int i;
    for (i=end; i>=0; i--)
    {
        if (i == 0)
        {
            //special case FIXME
            break;
        }
        else if (road->cars[i] == NULL)
        {
            //no car
            continue;
        }
        else if (road->cars[i-1] == NULL)
        {
            // no car in front
            // road->cars[i]->steps += 1;
            if (road->cars[i]->hasMoved == 1)
            {
                road->cars[i]->hasMoved = 0;
            }
            else
            {
                road->cars[i-1] = road->cars[i];
                road->cars[i] = NULL;
                *hasMoved = 1;
            }
        }
    }
}


/* Suggested TODO - Write a function to attempt to move the car at the first position on a given road
 * to the last position of a another given road.
 */
int moveCarToFirst(RoadData* road1, RoadData* road2)
{
    if (road1->cars[0] == NULL)
    {
        //no car
        return 0;
    }
    else if (road2->cars[road2->length-1] == NULL)
    {
        //no car in front of road2
        road2->cars[road2->length-1] = road1->cars[0];
        road1->cars[0] = NULL;
        return 1;
    }
    // there was a car at the end of road2
    // add car to addCarQueue?
    return 0;
}

/* Suggested TODO - Write a function to attempt to move a car from the add car queue onto the end of this road.
 */

int addCar(RoadData* road)
{
    if (road->cars[road->length-1] == NULL)
    {
        //no car at the back
        Car* car = dequeue(road->addCarQueue);
        if (car == NULL)
        {
            //no car in the queue
            return 0;
        }
        road->cars[road->length-1] = car;
        return 1;
    }
    // there was a car at the end of road
    return 0;
}

/* Suggested TODO - Write a function to update the current state of the traffic light based on the current cycle.
 */
//FIXME

/* Suggested TODO - Write a function to print the destinations of the cars on the road
 */
void printCars(RoadData* road)
{
    printf("Road of length %d\n", road->length);
    printf("Starting at %d and ending at %d\n", road->start, road->end);
    int i;
    for (i=0; i<road->length; i++)
    {
        if (road->cars[i] == NULL)
        {
            printf("_ ");
        }
        else
        {
            printf("%d ", road->cars[i]->destination);
        }
    }
    printf("\n");
}
 //printf("Cars on the road from %d to %d: \n", ????, ????);

void printRoads(int time, RoadData** roadArray, int numRoads)
{
    printf("CYCLE %d - PRINT_ROADS_EVENT - Current contents of the roads:\n", time);
    int i; 
    for ( i = 0; i < numRoads; i++)
    {
        printf("Cars on the road from %d to %d:\n", roadArray[i]->start, roadArray[i]->end);
        int j;
        for (j=0; j<roadArray[i]->length; j++)
        {
            if (roadArray[i]->cars[j] == NULL)
            {
                printf("_ ");
            }
            else
            {
                // printf("\e[1;31mTRUE\e[0m");
                printf("%d ", roadArray[i]->cars[j]->destination);
            }
        }
        printf("\n");
    }
    printf("\n");
}


