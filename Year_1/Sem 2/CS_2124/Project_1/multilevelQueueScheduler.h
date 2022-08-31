#ifndef _multilevelQueueScheduler_h
#define _multilevelQueueScheduler_h
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "process.h"
#include "queue.h"
#include "processSimulator.h"

/* struct schedule (only accessed in student written code)
 *
 * Data related to the order the processes should be scheduled
 * foreQueue and backQueue are the FOREGROUND and BACKGROUND queues respectively.
 *
 * Hint: It may also help to track the number of time steps that have been processed so far.
 */
typedef struct schedule
{
    Queue *foreQueue;
    Queue *backQueue;
    //TODO: Put the data for your schedule program here!


}  schedule;

schedule* createSchedule( );
bool isScheduleUnfinished( schedule *ps );
void addNewProcessToSchedule( schedule *ps, char *processName, priority p );
char* runNextProcessInSchedule( schedule *ps );
void freeSchedule( schedule *ps );

#endif

