#include <stdlib.h>

#include "multilevelQueueScheduler.h"

int min( int x, int y );

static const int STEPS_TO_PROMOTION = 50;
static const int FOREGROUND_QUEUE_STEPS = 5;

/* createSchedule
 * input: none
 * output: a schedule
 *
 * Creates and return a schedule struct.
 */
schedule* createSchedule( ) {
    /* TODO: malloc space for a new schedule and initialize the data in it */
    schedule* schedulex = (schedule*) malloc(sizeof(schedule));
    schedulex->foreQueue = createQueue();
    schedulex->backQueue = createQueue();

    return schedulex; /* TODO: Replace with your return value */
}

/* isScheduleUnfinished
 * input: a schedule
 * output: bool (true or false)
 *
 * Check if there are any processes still in the queues.
 * Return TRUE if there is.  Otherwise false.
 */
bool isScheduleUnfinished( schedule *ps ) {
    /* TODO: check if there are any process still in a queue.  Return TRUE if there is. */
    if( (isEmpty(ps->foreQueue)) && (isEmpty(ps->backQueue)) )
    {
      return false;
    }
    return true; /* TODO: Replace with your return value */
}

/* addNewProcessToSchedule
 * input: a schedule, a string, a priority
 * output: void
 *
 * Create a new process with the provided name and priority.
 * Add that process to the appropriate queue
 */
void addNewProcessToSchedule( schedule *ps, char *processName, priority p ) {
    /* TODO: complete this function.
    The function "initializeProcessData" in processSimulator.c will be useful in completing this. */
    LLNode* process_var = (LLNode*)malloc(sizeof(LLNode));
    process* qt = (process*)malloc(sizeof(process));
    process_var->qt = qt;
    process_var->qt->stepsWaited = 0;
    processData* thisispain = initializeProcessData(processName);
    process_var->qt->processName = processName;
    process_var->qt->data = thisispain;
    process_var->qt->stepsToRun = 0;
    process_var->qt->steps = 0;


    // Queue* qFront = (Queue*)malloc(sizeof(Queue));
    // Queue* qBack = (Queue*)malloc(sizeof(Queue));

    switch (p)
    {
      case 0:
        // if(ps->foreQueue==NULL)
        // {
        //   printf("test3\n");
        //   ps->foreQueue = qFront;
        //   ps->foreQueue->qFront->pNext = process_var;
        // }
        if(isEmpty(ps->foreQueue))
        {
          ps->foreQueue->qFront = process_var;
          ps->foreQueue->qRear = process_var;
          process_var->pNext = process_var;
        }
        else
        {
          ps->foreQueue->qRear->pNext = process_var;
          ps->foreQueue->qRear = process_var;
        }
        break;

      case 1:
        // if(ps->backQueue==NULL)
        // {
        //   ps->backQueue = qBack;
        //   ps->backQueue->qFront->pNext = process_var;
        // }
        if(isEmpty(ps->backQueue))
        {
          ps->backQueue->qFront = process_var;
          ps->backQueue->qRear = process_var;
          process_var->pNext = process_var;
        }
        else
        {
          ps->backQueue->qRear->pNext = process_var;
          ps->backQueue->qRear = process_var;
          process_var->pNext = ps->backQueue->qFront;
        }
        break;
    };
    // free( processName ); /* TODO: This is to prevent a memory leak but you should remove it once you create a process to put processName into */
}

/* runNextProcessInSchedule
 * input: a schedule
 * output: a string
 *
 * Use the schedule to determine the next process to run and for how many time steps.
 * Call "runProcess" to attempt to run the process.  You do not need to print anything.
 * You should return the string received from "runProcess".  You do not need to use/modify this string in any way.
 */
char* runNextProcessInSchedule( schedule *ps ) {
    /* TODO: complete this function.
    The function "runProcess", "promoteProcess", "loadProcessData", and "freeProcessData"
    in processSimulator.c will be useful in completing this.
    You may want to write a helper function to handle promotion */
    char *ret = NULL;
    int numSteps = 0;
    int validation;
    // below calculates how long the first process in the back queue has before it is promoted
    int minStepsToPromote = isEmpty(ps->backQueue) ? STEPS_TO_PROMOTION : (STEPS_TO_PROMOTION - ps->backQueue->qFront->qt->stepsWaited);
    
    /* TODO: Delete the following printf once you get the infinite loop fixed */
    // printf("IMPORTANT NOTE: There will be an intinite loop in runNextProcessInSchedule if you get isScheduleUnfinished and addNewProcessToSchedule working correctly\n"); 
    /* TODO: Uncomment the code below to dequeue elements from the two Queues and break your code out of the infinite loop*/
    if( !isEmpty(ps->foreQueue) )
    {
        // printf("FOREQUEUE\n");
        // printf("%s\n", ps->foreQueue->qFront->qt->processName);
        if (ps->foreQueue->qFront->qt->steps == 0)
        {
            // printf("test1\n");
            numSteps = min(FOREGROUND_QUEUE_STEPS, minStepsToPromote);
            validation = FOREGROUND_QUEUE_STEPS;
            // printf("numSteps: %d\n", numSteps);
            // printf("validation: %d\n", validation);
        }
        else
        {
            //testing2
            // printf("test2\n");
            numSteps = min(minStepsToPromote, ps->foreQueue->qFront->qt->steps);
            validation = ps->foreQueue->qFront->qt->steps;
            // printf("numSteps: %d\n", numSteps);
            // printf("validation: %d\n", validation);
        }
        loadProcessData( ps->foreQueue->qFront->qt->data );
        // printf("%d\n",ps->foreQueue->qFront->qt->steps);

        

        // runProcess( char *pName, char **ppSystemCall, int *pNumSteps )
        if (runProcess( ps->foreQueue->qFront->qt->processName, &ret, &numSteps ))
        {
            //If a process is finished, free its data
            // freeProcessData( ps->foreQueue->qFront->qt->data );
            //Remove the process from the queue
            freeProcessData();
            // free(ps->foreQueue->qFront->qt->data);
            free(ps->foreQueue->qFront->qt->processName);
            free(ps->foreQueue->qFront->qt);
            dequeue( ps->foreQueue );
        }
        else
        {
            //Checks if the background process is ready to be promoted
            if (minStepsToPromote - numSteps == 0)
            {
                //Promote the process
                // promoteProcess( char *pName, processData *pData )
                LLNode* temp = ps->backQueue->qFront;
                ps->backQueue->qFront->qt->stepsWaited = 0;
                if (ps->backQueue->qFront->pNext == ps->backQueue->qFront)
                {
                    ps->backQueue->qFront = NULL;
                    ps->backQueue->qRear = NULL;
                }
                else
                {
                    ps->backQueue->qFront = ps->backQueue->qFront->pNext;
                    ps->backQueue->qRear->pNext = ps->backQueue->qFront;
                }
                promoteProcess(temp->qt->processName, temp->qt->data);
                if (isEmpty(ps->foreQueue))
                {
                    ps->foreQueue->qFront = temp;
                    ps->foreQueue->qRear = temp;
                    temp->pNext = temp;
                }
                else
                {
                    ps->foreQueue->qRear->pNext = temp;
                    temp->pNext = ps->foreQueue->qFront;
                    ps->foreQueue->qRear = temp;
                }
            }
            //Check to make sure numSteps is the same as validation, if not, save the difference to the process under steps
            if (numSteps != validation)
            {
                ps->foreQueue->qFront->qt->steps = validation - numSteps;
            }
            else
            {
                ps->foreQueue->qFront->qt->steps = 0;
                // Also, move the process to the back of the queue
                enqueue( ps->foreQueue, dequeue( ps->foreQueue ) );
            }
            //debug
            // printf("End\n");
            // printf("numSteps: %d\n", numSteps);
            // printf("validation: %d\n", validation);
        }
        //Runs through the linked list back queue and updates how long they've been waiting
        // printf("TEST\n");
        if (!isEmpty(ps->backQueue))
        {
            LLNode* temp = ps->backQueue->qFront;
            while (temp != NULL)
            {
                // printf("TEST loop\n");
                // //debug
                // printf("%d\n", temp == NULL);
                // printf("%s\n", temp->qt->processName);
                temp->qt->stepsWaited += numSteps;
                // printf("TEST loop2\n");
                temp = temp->pNext;
                if (temp == ps->backQueue->qFront)
                {
                    break;
                }
            }
        }

        //dequeue(ps->foreQueue);
    }
    else if( !isEmpty(ps->backQueue) )
    {
        // printf("BACKQUEUE\n");
        numSteps = min(STEPS_TO_PROMOTION, minStepsToPromote);
        validation = numSteps;
        loadProcessData( ps->backQueue->qFront->qt->data );

        

        // runProcess( char *pName, char **ppSystemCall, int *pNumSteps )
        if (runProcess( ps->backQueue->qFront->qt->processName, &ret, &numSteps ))
        {
            //If a process is finished, free its data
            // freeProcessData( ps->foreQueue->qFront->qt->data );
            //Remove the process from the queue
            freeProcessData();
            // free(ps->backQueue->qFront->qt->data);
            free(ps->backQueue->qFront->qt->processName);
            free(ps->backQueue->qFront->qt);
            dequeue( ps->backQueue );
        }
        else
        {
            //Checks if the background process is ready to be promoted
            if (minStepsToPromote - numSteps == 0)
            {
                //Promote the process
                // // promoteProcess( char *pName, processData *pData )
                LLNode* temp = ps->backQueue->qFront;
                ps->backQueue->qFront->qt->stepsWaited = 0;
                if (ps->backQueue->qFront->pNext == ps->backQueue->qFront)
                {
                    ps->backQueue->qFront = NULL;
                    ps->backQueue->qRear = NULL;
                }
                else
                {
                    ps->backQueue->qFront = ps->backQueue->qFront->pNext;
                    ps->backQueue->qRear->pNext = ps->backQueue->qFront;
                }
                promoteProcess(temp->qt->processName, temp->qt->data);

                if (isEmpty(ps->foreQueue))
                {
                    ps->foreQueue->qFront = temp;
                    ps->foreQueue->qRear = temp;
                    temp->pNext = temp;
                }
                else
                {
                    ps->foreQueue->qRear->pNext = temp;
                    temp->pNext = ps->foreQueue->qFront;
                    ps->foreQueue->qRear = temp;
                }
                // printf("%s\n", ps->foreQueue->qRear->qt->processName);
                //Moves the process from the back queue to the front queue
                // enqueue( ps->foreQueue, dequeue( ps->backQueue ) );
            }
            //Check to make sure numSteps is the same as validation, if not, save the difference to the process under steps
            // if (numSteps != validation)
            // {
            //     ps->backQueue->qFront->qt->steps = validation - numSteps;
            // }
            // else
            // {
                // ps->backQueue->qFront->qt->steps = 0;
                // // Also, move the process to the back of the queue
                // enqueue( ps->backQueue, dequeue( ps->backQueue ) );
            // }
        }        
        //Runs through the linked list back queue and updates how long they've been waiting
        if (!isEmpty(ps->backQueue))
        {
            LLNode* temp = ps->backQueue->qFront;
            while (temp != NULL)
            {
                temp->qt->stepsWaited += numSteps;
                temp = temp->pNext;
                if (temp == ps->backQueue->qFront)
                {
                    break;
                }
            }
        }
    }
    
    
    /* your call to runProcess will look something like this: */
    //bool b = runProcess( /* name of process */, &ret, &numSteps );
    
    return ret; /* This will be the char* that runProcess stores in ret when you call it. */
}

/* freeSchedule
 * input: a schedule
 * output: none
 *
 * Free all of the memory associated with the schedule.
 */
void freeSchedule( schedule *ps ) {
    /* TODO: free any data associated with the schedule as well as the schedule itself.
    the function "freeQueue" in queue.c will be useful in completing this. */

    //The two below if statements are for redundancy in case the schedule is freed with processes still in it
    if (!isEmpty(ps->foreQueue))
    {
      LLNode* prev = ps->foreQueue->qFront;
      LLNode* curr = ps->foreQueue->qFront->pNext;
      if (curr != NULL && (prev != curr))
      {
        free(prev);
        while ( curr != ps->foreQueue->qRear )
        {
          prev = curr;
          curr = curr->pNext;
          free(prev);
        }
      }
    }
    if (!isEmpty(ps->backQueue))
    {
      LLNode* prev = ps->backQueue->qFront;
      LLNode* curr = ps->backQueue->qFront->pNext;
      if (curr != NULL && (prev != curr))
      {
        free(prev);
        while ( curr != ps->backQueue->qRear )
        {
          prev = curr;
          curr = curr->pNext;
          free(prev);
        }
      }
    }
    freeQueue(ps->foreQueue);
    freeQueue(ps->backQueue);
    free(ps);
}

int min( int x, int y ){
    if( x<y )
        return x;
    return y;
}
