#include "trafficSimulator.h"
#include "road.h"

//TO BE DELETED
#include "hashTable.h"
#include "equalsInt.h"
#include "queue.h"
#include "road.h"
#include "graph.h"


/* Function declarations: */
TrafficData* readTrafficDataFromInputFile( char* name );
void freeTrafficData(TrafficData* trafficData);

/* printNames
 * input: none
 * output: none
 *
 * Prints names of the students who worked on this solution
 */
void printNames( )
{
    /* TO DO : Fill in you and your partner's names (or N/A if you worked individually) */
    printf("This solution was completed by:\n");
    printf("YYYY\n");
    printf("\e[40m\e[1m\e[36m\e[6mJ\e[37mu\e[36ml\e[37mia\e[36mn\e[37mu\e[36ms\e[37m Au\e[36mr\e[37me\e[36ml\e[37miu\e[36rs\e[0m\n");

}


/* trafficSimulator
 * input: char* name of file to read
 * output: N/A
 *
 * Read in the traffic data from the file whose name is stored in char* filename
 * Simulate the rules outlined in the project 2 description
 */
void trafficSimulator( char* filename )
{
    /* TO DO: complete this function */

    // access road array via
    // trafficData->roadArray[i]->roadData



    /* Read in the traffic data.  It's recommended you put the code to do this in the function readTrafficDataFromInputFile. */
    TrafficData* trafficData = readTrafficDataFromInputFile(filename);
    /* Loop until all events processed and either all cars reached destination or gridlock has occurred */
    int time = 0;
    int timeSinceLastMove = 0;
    do //change to a do while??? It may not run because we haven't added any cars yet
    {
        int hasMoved = 0;
        /* Loop on events associated with this time step */
        if (!isEmptyPQ(trafficData->eventQueue))
        {
            while(getFrontPriority(trafficData->eventQueue) == time)
            {
                // curr = dequeuePQ(trafficData->eventQueue);
                // PQNode* curr = trafficData->eventQueue->qFront;
                // Event* currEvent = curr->qt;
                Event* currEvent = dequeuePQ(trafficData->eventQueue);
                if(currEvent->event == ADD_CAR_EVENT)
                {
                    //add car to road
                    int fromVertex = currEvent->carEventPointer->fromVertex;
                    int toVertex = currEvent->carEventPointer->toVertex;
                    int destination = currEvent->carEventPointer->destination;
                    // find the road going from fromVertex to toVertex, malloc a new car with the destination, and add it to the road's addCarQueue
                    // TODO
                    int i;
                    for (i=0; i<trafficData->numOfRoads; i++)
                    {
                        if (trafficData->roadArray[i]->end == fromVertex && trafficData->roadArray[i]->start == toVertex)
                        {
                            Car* newCar = malloc(sizeof(Car));
                            newCar->destination = destination;
                            newCar->steps = time; //keep track of when the car was added for final output
                            printf("CYCLE %d - ADD_CAR_EVENT - Cars enqueued on road from %d to %d\n", time, fromVertex, toVertex);
                            //TODO: add print statement for adding cars
                            enqueue(trafficData->roadArray[i]->addCarQueue, newCar);
                            break;
                        }
                    }
                    
                    trafficData->numOfCars++;
                    free(currEvent->carEventPointer);
                    // delete the event from the queue, and all associated malloced memory
                    // PQNode* temp = curr;
                    // curr = curr == NULL ? NULL : curr->pNext;
                    // if (temp->qt != NULL)
                    // {
                    //     if (temp->qt != NULL)
                    //     {
                    //         if (temp->qt->carEventPointer != NULL)
                    //         {
                    //             free(temp->qt->carEventPointer);
                    //         }
                    //         free(temp->qt);
                    //     }
                    //     free(temp);
                    // }
                }
                else if(currEvent->event == PRINT_ROADS_EVENT)
                {
                    //print roads
                    // 1+1; //added this to comment out below line, but still have something in this if statement
                    printRoads(time, trafficData->roadArray, trafficData->numOfRoads); //TODO: Make printRoads function
                    // PQNode* temp = curr;
                    // curr = curr == NULL ? NULL : curr->pNext;
                    // // free(temp->qt->carEventPointer); // comment out if there is an error? If no error, combine these two from the if and else into a single block after
                    // if (temp->qt != NULL)
                    // {
                    //     if (temp->qt->carEventPointer != NULL)
                    //     {
                    //         free(temp->qt->carEventPointer);
                    //     }
                    //     free(temp->qt);
                    // }
                    // free(temp);
                }
                if (currEvent != NULL)
                {
                    // if (currEvent->carEventPointer != NULL) //Not needed as it is never init for the print events
                    // {
                    //     free(currEvent->carEventPointer);
                    // }
                    // if (currEvent->event == ADD_CAR_EVENT)
                    // {
                    //     free(currEvent->carEventPointer);
                    // }
                    free(currEvent);
                }
                if (isEmptyPQ(trafficData->eventQueue))
                {
                    break;
                }
            }
        }
        // trafficData->eventQueue->qFront->priority
        // check if first event's priority is equal to time, if so, process it and move on to the next event until it's not equal to time
            // make sure to dequeue the event and free all data associated with it



        // CHANGE LIGHTS
        int i;
        for (i=0;i<trafficData->numOfRoads;i++)
        {
            trafficData->roadArray[i]->currCycle += 1;
            if (trafficData->roadArray[i]->currCycle == trafficData->roadArray[i]->greenOnLength)
            {
                trafficData->roadArray[i]->light = 0;
            }
            else if (trafficData->roadArray[i]->currCycle == (trafficData->roadArray[i]->greenOnLength + trafficData->roadArray[i]->redOnLength))
            {
                trafficData->roadArray[i]->light = 1;
            }
            if (trafficData->roadArray[i]->currCycle == trafficData->roadArray[i]->reset)
            {
                trafficData->roadArray[i]->currCycle = 0;
            }
        }




        /* First try to move through the intersection */
        // for (i=0; i<trafficData->roadNetwork->numVertices; i++)
        for (i=0; i<trafficData->numOfRoads; i++)
        {
            RoadData* road = trafficData->roadArray[i];
            if (road->light == 1) // GREEN
            {
                if (trafficData->roadArray[i]->cars[0] != NULL)
                {
                    // TODO: check if front car has reached destination, if so, dequeue and free it, and decrement numOfCars
                    if (road->end == road->cars[0]->destination)
                    {
                        printf("CYCLE %d - Car successfully traveled from %d to %d in %d time steps.\n", time, road->start, road->end, time - road->cars[0]->steps+1); //added 1 because outputs in example had 41 timesteps at timestep 40, for example
                        free(road->cars[0]);
                        hasMoved = 1;
                    }
                    else
                    {
                        int nextVertex =-1;
                        //                                         graph                 from       to                          pnext
                        bool success = getNextOnShortestPath(trafficData->roadNetwork, road->end, road->cars[0]->destination, &nextVertex); //nextVertex is passed by address to be returned by address?
                        if (success)
                        {
                            // check if next road is open
                            int j;
                            for (j=0; j<trafficData->numOfRoads; j++)
                            {
                                if (trafficData->roadArray[j]->end == nextVertex)
                                {
                                    if (trafficData->roadArray[j]->start == road->end)
                                    {
                                        if (trafficData->roadArray[j]->cars[trafficData->roadArray[j]->length-1] == NULL) // last spot on road is empty
                                        {
                                            // remove car from road 1
                                            trafficData->roadArray[i]->cars[trafficData->roadArray[i]->length-1] = trafficData->roadArray[j]->cars[0];
                                            trafficData->roadArray[j]->cars[0]->hasMoved = 1;
                                            trafficData->roadArray[j]->cars[0] = NULL;
                                            // add car to road 2
                                            hasMoved = 1;
                                        }
                                        break;
                                    }
                                }                                                           
                            }
                        }
                    }
                }
            }
            // RoadData* currRoad = NULL;
            // bool success = getVertexByIndex(trafficData->roadNetwork, i, currRoad);
            // if (success) {
            //     if ()
            // }
            // look at all the cars at the front of every road going to that intersection,
            // see if the road's light is green, if so,
            // then run getNextOnShortestPath on that car to find the next road to go to
            // check if the next road's last index is empty, if so, move the car
            // if not, add the car to the next road's addCarQueue
            // do we need to move it to the last index or as far as it can drive until it hits a car??????????????
        
        
        // OR is the addCarQueue for addCar events?
        }


        /* Second move cars onto road if possible */
        for (i=0; i<trafficData->roadNetwork->numVertices; i++)
        {
            int i;
            for (i=0; i<trafficData->numOfRoads; i++)
            {
                if (trafficData->roadArray[i]->cars[trafficData->roadArray[i]->length-1] == NULL)
                {
                    // printf("test3\n");
                    if (!isEmpty(trafficData->roadArray[i]->addCarQueue))               
                    {
                        // bold red saying TEST
                        // printf("\e[1\e[31mTEST\e[0m\n");
                        // printf("from: %d, to: %d\n", trafficData->roadArray[i]->start, trafficData->roadArray[i]->end);
                        //deque the car from the addCarQueue and add it to the end of the road
                        // LLNode* node = dequeue(trafficData->roadArray[i]->addCarQueue);
                        // Car* car = node->qt;
                        Car* car = dequeue(trafficData->roadArray[i]->addCarQueue);
                        car->hasMoved = 1;
                        hasMoved = 1;
                        trafficData->roadArray[i]->cars[trafficData->roadArray[i]->length-1] = car;
                    }
                }
            }
            // look at all the cars in the of every road,
            // see if the road's light is green, if so, then
            // check if the that road's last index is empty, if so, move the car
        }


        /* Third move cars forward on every road (only those that haven't moved yet this time step ??????????) */
        // loop through all the roads and run moveCars on each one
        // mark the cars that moved from the intersections with a boolean??
        for (i=0; i<trafficData->numOfRoads; i++)
        {
            moveCars(trafficData->roadArray[i], &hasMoved);
        }

        printf("%d\n", timeSinceLastMove);
        time++;
        if (hasMoved == 0)
        {
            timeSinceLastMove++;
            if (timeSinceLastMove == trafficData->longestCycle+2) //1
            {
                printf("CYCLE %d - Gridlock has been detected.\n", time);
                trafficData->gridlock = 1;
            }
        }
        else
        {
            timeSinceLastMove = 0;
        }
    } while(trafficData->numOfCars != 0 && trafficData->gridlock == 0);
    freeTrafficData(trafficData);
}

/* readTrafficDataFromInputFile
 * input: char* filename of file to read
 * output: TrafficData* which stores the data of this road network
 *
 * Create a new TrafficData variable and read in the traffic data from the file whose name is stored in char* filename
 */
TrafficData* readTrafficDataFromInputFile( char* filename )
{
    /* Optional TO DO: */
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    TrafficData* trafficData = (TrafficData*)malloc(sizeof(TrafficData)); //???
    trafficData->gridlock = 0;
    trafficData->numOfCars = 0;
    int numOfVertex;
    int numOfRoads;
    fscanf(file, "%d %d\n", &numOfVertex, &numOfRoads);
    trafficData->roadArray = (RoadData**)malloc(sizeof(RoadData*)*numOfRoads); // RoadData** ??
    int curr = 0;
    trafficData->roadNetwork = createGraph(numOfVertex);
    // printf("# of vertex: %d\n", numOfVertex);
    trafficData->eventQueue = createPQ();
    trafficData->longestCycle = 0;
    trafficData->numOfRoads = 0;
    int i;
    fscanf(file, "\n\n");
    // int** adjacencyMatrix = malloc(sizeof(int*) * numOfVertex);
    for (i=0; i < numOfVertex; i++)
    {
        // int p = getIndex(trafficData->roadNetwork, i);
        // printf("index: %d, ",p);
        addVertex(trafficData->roadNetwork, i);
        // printf("i: %d\n",i);
    }
    for (i=0; i < numOfVertex; i++) //Makes roads
    {
        // int p = getIndex(trafficData->roadNetwork, i);
        // printf("index: %d, ",p);
        // addVertex(trafficData->roadNetwork, i);
        // printf("i: %d\n",i);
        int size;
        fscanf(file, "%d\n", &size);
        // adjacencyMatrix[i] = malloc(sizeof(int) * numOfVertex);
        // int k;
        // for (k=0; k < numOfVertex; k++)
        // {
        //     adjacencyMatrix[i][k] = NULL;
        // }
        // form: <from vertex> <length>[tab]<green on> <green off> <cycle resets>
        int j;
        for (j=0; j < size; j++)
        {
            int fromVertex;
            int length;
            int greenOn;
            int greenOff;
            int cycleResets;
            fscanf(file, "%d %d     %d %d %d\n", &fromVertex, &length, &greenOn, &greenOff, &cycleResets);
            // adjacencyMatrix[i][fromVertex] = length;
            setEdge(trafficData->roadNetwork, fromVertex, i, length); //Switch i and from vertex??
            trafficData->longestCycle = cycleResets > trafficData->longestCycle ? cycleResets : trafficData->longestCycle;
            edgeType data = createRoad(length, fromVertex, i);
            data->greenOnLength = greenOn;
            data->redOnLength = greenOff;
            data->currCycle = 0;
            data->reset = cycleResets;
            trafficData->numOfRoads++;
            trafficData->roadArray[curr++] = data; // &data??
            setEdgeData(trafficData->roadNetwork, fromVertex, i, data);
        }
    }
    fscanf(file, "\n\n");
    int numOfCarCommands;
    fscanf(file, "%d\n", &numOfCarCommands);
    fscanf(file, "\n\n");
    // trafficData->addCarArray = (addCarEvent*)malloc(sizeof(addCarEvent));
    for (i=0; i < numOfCarCommands; i++) //Adds cars
    {
        int fromVertex;
        int toVertex;
        int time;
        fscanf(file, "%d %d %d\n", &fromVertex, &toVertex, &time);
        int numOfCars;
        fscanf(file, "%d\n", &numOfCars);
        int* destinationsByCar;
        destinationsByCar = malloc(sizeof(int) * numOfCars);
        PQNode* node = (PQNode*)malloc(sizeof(PQNode));
        Event* qt = (Event*)malloc(sizeof(Event));
        node->qt = qt;
        node->priority = time;
        // printf("Error is below this\n");
        // node->qt->timestep = time; //???
        // printf("Error is above this\n");
        node->pNext = NULL;
        node->qt->event = ADD_CAR_EVENT;
        int j;
        for (j=0; j < numOfCars; j++)
        {
            fscanf(file, "%d\n", &destinationsByCar[j]);
            addCarEvent* newCarCommand = (addCarEvent*)malloc(sizeof(addCarEvent));
            newCarCommand->destination = destinationsByCar[j];
            newCarCommand->fromVertex = fromVertex;
            newCarCommand->toVertex = toVertex;
            node->qt->carEventPointer = newCarCommand;
            //Make a car object??? Or do it later during the command?
            // free(newCarCommand); // POSSSIBLE ERROR
        }
        // append this command to a priority queue??
        enqueueByPriority(trafficData->eventQueue, node->qt, time); //??
        free(destinationsByCar);
        free(node);
    }
    
    fscanf(file, "\n\n");
    int numOfPrintCommands;
    fscanf(file, "%d\n", &numOfPrintCommands);
    int* commandTimeStep;
    commandTimeStep = malloc(sizeof(int) * numOfPrintCommands);
    fscanf(file, "\n\n");
    for (i=0; i < numOfPrintCommands; i++) //Prints
    {
        fscanf(file, "%d\n", &commandTimeStep[i]);
        PQNode* node = (PQNode*)malloc(sizeof(PQNode));
        Event* qt = (Event*)malloc(sizeof(Event));
        node->qt = qt;
        node->priority = commandTimeStep[i];
        // node->qt->timestep = commandTimeStep[i]; //???
        node->pNext = NULL;
        node->qt->event = PRINT_ROADS_EVENT;
        enqueueByPriority(trafficData->eventQueue, node->qt, commandTimeStep[i]); // ??
        free(node);
        
    }
    free(commandTimeStep);
    fclose(file);
    return trafficData; /* Optional TO DO: Replace this with your TrafficData pointer */
}


void freeTrafficData(TrafficData* trafficData)
{
    //MAY NOT HAVE DELETED EVERYTHING PROPERLY ???
    // free(trafficData->addCarArray);
    // go through eventQueue and free all the events
    //debug
    // printf("isEmptyPQ: %d\n", isEmptyPQ(trafficData->eventQueue));
    if (!isEmptyPQ(trafficData->eventQueue))
    {
        Event* curr = dequeuePQ(trafficData->eventQueue);
        while (curr != NULL)                                                           
        {
            // if (curr->qt != NULL)
            // {
            //     // free(curr->qt->carEventPointer);
            //     if (curr->qt->carEventPointer != NULL)
            //     {
            //         free(curr->qt->carEventPointer);                                        
            //     }
            //     free(curr->qt);
            // }
            // // free(curr->priority);
            // free(curr);
            // curr = next;
            // if (curr != NULL)
            // {
            //     next = curr->pNext;
            // }
            if (curr->event == ADD_CAR_EVENT)
            {
                free(curr->carEventPointer);
            } 
            free(curr);
            curr = dequeuePQ(trafficData->eventQueue);
        }
    }
    // printf("isEmptyPQ: %d\n", isEmptyPQ(trafficData->eventQueue));
    // free the roads
    freePQ(trafficData->eventQueue);
    freeGraph(trafficData->roadNetwork);
    int i;
    for (i = 0; i<trafficData->numOfCars; i++)
    {
        // Also need to free the 'Cars** car' array and 'Queue* addCarQueue' members of the Road Struct
            // Done
        if (!isEmpty(trafficData->roadArray[i]->addCarQueue))
        {
            Car* curr = dequeue(trafficData->roadArray[i]->addCarQueue);
            while (curr != NULL)
            {
                free(curr);
                curr = dequeue(trafficData->roadArray[i]->addCarQueue);
            }
        }
        freeQueue(trafficData->roadArray[i]->addCarQueue);
        // int j;
        // for (j=0; i<trafficData->roadArray[i]->length; i++)
        // {
        //     free(trafficData->roadArray[i]->cars[j]);
        // }
        // free(trafficData->roadArray[i]); //This is off the number of cars, I need to switch over to number of roads?
        //??????
    }
    for (i = 0; i < trafficData->numOfRoads; i++)
    {
        freeRoad(trafficData->roadArray[i]);
    }
    free(trafficData->roadArray);
    free(trafficData);
}