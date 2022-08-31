#include <stdlib.h>

#include "multilevelQueueScheduler.h"

int min( int x, int y );
void helper(Queue* stack, char** ret, int numStepsToStop, int val, bool q2);
void helper2(schedule* ps, int minStepsToPromote, bool flag);

static const int STEPS_TO_PROMOTION = 50;
static const int FOREGROUND_QUEUE_STEPS = 5;

/* createSchedule
 * input: none
 * output: a schedule
 *
 * Creates and return a schedule struct.
 */
schedule* createSchedule( ) {
    /* TODO: initialize data in schedule */
    // Queue* bqueue = createQueue();
    // Queue* fqueue = createQueue();
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
    queueType qt = (queueType)malloc(sizeof(queueType));
    process_var->qt = qt;
    process_var->qt->stepsRan = 0;
    processData* thisispain = initializeProcessData(processName);
    process_var->qt->processName = processName;
    process_var->qt->data = thisispain;
    process_var->qt->stepsToRun = 0;


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
        process_var->qt->steps = 0;
        break;
    };

    //free( processName ); /* TODO: This is to prevent a memory leak but you should remove it once you create a process to put processName into */
}

/* runNextProcessInSchedule
 * input: a schedule
 * output: a string
 *
 * Use the schedule to determine the next process to run and for how many time steps.
 * Call "runProcess" to attempt to run the process.  You do not need to print anything.
 * You should return the string "runProcess" returns.  You do not need to use/modify this string in any way.
 */
char* runNextProcessInSchedule( schedule *ps ) {
    /* TODO: complete this function.
    The function "runProcess", "promoteProcess", "loadProcessData", and "freeProcessData"
    in processSimulator.c will be useful in completing this.
    You may want to write a helper function to handle promotion */
    char *ret = NULL;

    if (!isEmpty(ps->foreQueue))
    {
      int numStepsToStop = ps->foreQueue->qFront->qt->stepsToRun == 0 ? FOREGROUND_QUEUE_STEPS : ps->foreQueue->qFront->qt->stepsToRun;
      int minStepsToPromote = STEPS_TO_PROMOTION;

      if (!isEmpty(ps->backQueue))
      {
        LLNode* curr = ps->backQueue->qFront;
        do
        {
          minStepsToPromote = min(minStepsToPromote, STEPS_TO_PROMOTION - curr->qt->stepsRan);
          curr = curr->pNext;
        } while (curr != ps->backQueue->qRear);
      }
      // printf("num: %d and %d\n", numStepsToStop, minStepsToPromote);
      if (minStepsToPromote < numStepsToStop)
      {
        numStepsToStop = minStepsToPromote;
        // helper(ps->foreQueue, ret, minStepsToPromote, val);
        // helper2(ps, minStepsToPromote, true);
        // helper(ps->foreQueue, ret, numStepsToStop - minStepsToPromote, val);
        // helper2(ps, numStepsToStop - minStepsToPromote, true);
      }
      int val = numStepsToStop;
      ps->foreQueue->qFront->qt->stepsRan = numStepsToStop;
      // else
      // {
        helper(ps->foreQueue, &ret, numStepsToStop, val, true);
        helper2(ps, numStepsToStop, true);
      // }


    }
    else if(!isEmpty(ps->backQueue))
    {
      int numStepsToStop = STEPS_TO_PROMOTION - ps->backQueue->qFront->qt->stepsRan;
      // printf("%d\n", numStepsToStop);
      LLNode* curr = ps->backQueue->qFront;
      numStepsToStop = min(numStepsToStop, STEPS_TO_PROMOTION - curr->qt->stepsRan);
      if (numStepsToStop <= 0)
      {
        curr->qt->stepsRan=0;
        promoteProcess(curr->qt->processName, curr->qt->data);
        queueType qt = dequeue(ps->foreQueue);
        return NULL;;
      }
      curr = curr->pNext;
      LLNode* prev = ps->backQueue->qFront->pNext;

      do
      {
        numStepsToStop = min(numStepsToStop, STEPS_TO_PROMOTION - curr->qt->stepsRan);
        if (numStepsToStop <= 0)
        {
          curr->qt->stepsRan=0;
          prev->pNext = curr->pNext;
          promoteProcess(curr->qt->processName, curr->qt->data);
          return NULL;;
        }
        curr = curr->pNext;
      } while (curr != ps->backQueue->qRear);
      int val = numStepsToStop;
      // printf("n1: %d\nn2: %d\n", ps->backQueue->qFront->qt->stepsToGo, ps->backQueue->qFront->qt->data->heap[1] - ps->backQueue->qFront->qt->data->heap[5]);
      // while( numStepsToStop != numSteps )
      // {
      helper(ps->backQueue, &ret, numStepsToStop, val, false);
      helper2(ps, numStepsToStop, true);
    }
    // else
    // {
    //   //Nothing in the schedule
    //   return ret;
    // }
    /* TODO: Delete the following printf once you get the infinite loop fixed */
    //printf("IMPORTANT NOTE: There will be an infinite loop in runNextProcessInSchedule if you get isScheduleUnfinished and addNewProcessToSchedule working correctly\n");
    /* TODO: Uncomment the code below to dequeue elements from the two Queues and break your code out of the infinite loop
    if( !isEmpty(ps->foreQueue) )
        dequeue(ps->foreQueue);
    else if( !isEmpty(ps->backQueue) )
        dequeue(ps->backQueue);
    */

    /* your call to runProcess will look something like this: */
    // bool b = runProcess( /* name of process */, &ret, &numSteps );

    return ret; /* TODO: be sure to store the value returned by runProcess in ret */
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

}

int min( int x, int y ){
    if( x<y )
        return x;
    return y;
}


void helper(Queue* stack, char** ret, int numStepsToStop, int val, bool q2)
{
  bool question = true;
  // while (numStepsToStop != val)
  // {
    loadProcessData(stack->qFront->qt->data);

    question = runProcess(stack->qFront->qt->processName, ret, &numStepsToStop);
    // stack->qFront->qt->stepsRan += numStepsToStop;
    // printf("num: %d\nval: %d\n", numStepsToStop, val);
    // if ((numStepsToStop != val) && !question)
    // {
    //   numStepsToStop = val - numStepsToStop;
    //   val = numStepsToStop;
    //   question = runProcess(stack->qFront->qt->processName, &ret, &numStepsToStop);
    //   stack->qFront->qt->stepsRan += numStepsToStop;
    // }
  // }
  // printf("%d\n", question);
  if (question)
  {
    // ELEPHANT
    // freeProcessData();
    queueType qt = dequeue(stack);
    if (isEmpty(stack))
    {
      stack->qFront = NULL;
      stack->qRear = NULL;
    }
    // printf("testing2\n");
    // printf("%d\n", *qt==NULL);
    // printf("test2\n");
    // free(qt->data);
    // printf("test\n");
    // free(dequeue(ps->foreQueue));
    // freeProcessData();
    //##############################################
    //##############################################
    // MIGHT HAVE SOME MEMORY ISSUES?
    //##############################################
    //##############################################
  }
  else if (numStepsToStop == val && q2) /* Not applicable to backQueue */
  {
    stack->qFront->qt->stepsToRun = 0;
    enqueue(stack,dequeue(stack));
  }
  else
  {
    stack->qFront->qt->stepsToRun = val - numStepsToStop;
  }
}

void helper2(schedule* ps, int minStepsToPromote, bool flag)
{
  // printf("%d\n", !isEmpty(ps->backQueue));
  if (!isEmpty(ps->backQueue))
  {
    //prints processes names left in backqueue

    //printf("%s\n", ps->backQueue->qFront->qt->processName);
    LLNode* prev = NULL;
    LLNode* curr = ps->backQueue->qFront;
    do
    {


      // if (flag)
      // {
      //   1+1;//curr->qt->stepsRan += minStepsToPromote;
      // }
      if (curr->qt->stepsRan >= STEPS_TO_PROMOTION)
      {
        curr->qt->stepsRan=0;
        if (prev == NULL)
        {
          if (curr == curr->pNext)
          {
            ps->backQueue->qFront = NULL;
            ps->backQueue->qRear = NULL;
            // FREE CURR somehow
          }
          else
          {
            ps->backQueue->qFront = curr->pNext;
            // FREE CURR somehow
          }
        }
        else
        {
          prev->pNext = curr->pNext;
          // FREE CURR somehow
          if (ps->backQueue->qRear == curr)
          {
            ps->backQueue->qRear = prev;
          }
        }
        if (ps->backQueue->qFront == curr)
        {
          ps->backQueue->qFront = curr->pNext;
        }
        promoteProcess(curr->qt->processName, curr->qt->data);

      }
      prev = curr;
      curr = curr->pNext;
    } while (curr != ps->backQueue->qRear);
  }
}
