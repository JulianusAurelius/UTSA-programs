#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "processSimulator.h"

char* runProcessForOneTimeStep( char *pName );
bool authenticationRAM( char *pName );
bool authentication( char *pName, processData *pData  );
void startProcess( char *pName, processData *pData );

static int time = 1;
static int nameNum = 0;
static processData *RAM = NULL;

/* initializeProcessData
 * input: the process name
 * output: initialized data for the process
 *
 * Initialize the data for a process.
 * Call this when a process is first added to your queue
 */
processData* initializeProcessData( char *processName ){
    processData* pData = (processData*)malloc(sizeof(processData));
    char temp[21];
    char intStr[3];
    char *priorityName;
    int i;

    if( pData==NULL ){
        fprintf(stderr, "initializeProcessData: Unable to allocate data.");
        exit(-1);
    }
    for(i=0; i<21; i++)
        pData->PN21[i] = 0;
    strncpy( pData->PN21, processName, 20 );

    //printf("%s\n",processName);
    sscanf( processName, "%*[^|]|%20s", temp );
    sscanf( temp, "%3[^|]|%20s", pData->TLN, temp );
    for( i=0; i<=4; i++ ){
        //printf("%s\n",temp);
        sscanf( temp, "%2[^|]|%20s", intStr, temp );
        sscanf( intStr, "%d", &pData->heap[i] );
    }
    while( i<=26 ){
        pData->heap[i]=0;
        i++;
    }
    pData->heap[6] = pData->heap[2];
    pData->heap[10]=25;
    pData->heap[7] = processName[0]=='B';

    pData->heap[8]=pData->heap[4];

    pData->heap[1] = max(pData->heap[1]/powInt(2,abs(pData->heap[7]-1)),1);
    pData->heap[10]=pData->heap[10]<<1;
    pData->heap[11]=time;

    if( pData->heap[7] ){
        priorityName = "BACKGROUND";
    }
    else{
        priorityName = "FOREGROUND";
    }

    printf( "Process data created: %s-%d (%s for %d steps)\n", pData->TLN, pData->heap[0], priorityName, pData->heap[1] );

    return pData;
}

/* runProcess
 * input: the process name and a pointer to an int that contains the number of steps to run for
 * output: a bool which is true if the process finished and false if it is still incomplete
 *
 * return by reference: 
 * 1) stores at pNumSteps the number of steps run prior to the process finishing or a system call 
 * 2) stores at ppSystemCall a string which is the name of a process which is started by this one OR NULL if no process is started 
 *
 * Attempts to run the process currently loaded in RAM for k time steps.
 * If this process makes a system call the execution it will set ppSystemCall to that process's name, otherwise it sets ppSystemCall to NULL.
 * If the process completes or a system call occurs runProcess suspends execution of this process and it writes the number of steps completed at *pNumSteps.
 */
bool runProcess( char *pName, char **ppSystemCall, int *pNumSteps ){
    int i = 0;
    *ppSystemCall = NULL;

    if( !authenticationRAM( pName ) ){
        exit(-1);
    }

    printf( "Attempting to run process: %s-%d for %d steps\n", RAM->TLN, RAM->heap[0], *pNumSteps );

    while( i<*pNumSteps && *ppSystemCall == NULL && RAM->heap[5]<RAM->heap[1] ){
        *ppSystemCall = runProcessForOneTimeStep( pName );
        i++;
    }
    
    *pNumSteps = i;

    if( RAM->heap[5]>=RAM->heap[1] && i==0 ){
        printf( "ERROR - Attempting to run process that has already completed: %s-%d\n", RAM->TLN, RAM->heap[0]  ); 
        exit(-1);
    }
    else if( RAM->heap[5]==RAM->heap[1] ){
        printf( "Process completed after %d steps: %s-%d\n", i, RAM->TLN, RAM->heap[0] );
        return true;
    }
    else if( *ppSystemCall != NULL )
        printf( "Execution interrupted after %d steps: %s-%d\n", i, RAM->TLN, RAM->heap[0] );
    
    return false;
}

/* loadProcessData
 * input: a processData to be loaded into RAM
 * output: a string
 *
 * Prints out message saying which data was evicted and which was loaded.  If the given data is already loaded nothing is printed.
 * In the real world the RAM can contain data from multiple processes but we're keeping it simple :)
 */
void loadProcessData( processData *pData ){
    if( pData != RAM ){
        if( RAM != NULL )
            printf( "Process data evicted: %s-%d (run for %d/%d steps so far)\n", RAM->TLN, RAM->heap[0], RAM->heap[5], RAM->heap[1] );
        RAM = pData;
        printf( "Process data loaded: %s-%d (run for %d/%d steps so far)\n", RAM->TLN, RAM->heap[0], RAM->heap[5], RAM->heap[1] );
    }
}


/* promoteProcess
 * input: the process name and the process data
 * output: a string
 *
 * Prints out message indicating a BACKGROUND process is being promoted to FOREGROUND
 */
void promoteProcess( char *pName, processData *pData ){
    if( authentication( pName, pData ) ){
        if( pData->heap[7] ) {
            pData->heap[7] = 0;
            if( !(time-pData->heap[11]-pData->heap[10]) )
                printf( "Process promoted: %s-%d (run for %d/%d steps so far)\n", pData->TLN, pData->heap[0], pData->heap[5], pData->heap[1] );
            else if( time-pData->heap[11]-pData->heap[10]<0 )
                printf( "ERROR - Process promoted %d step(s) too soon: %s-%d (run for %d/%d steps so far)\n", -1*(time-pData->heap[11]-pData->heap[10]), pData->TLN, pData->heap[0], pData->heap[5], pData->heap[1] );
            else
                printf( "ERROR - Process promoted %d step(s) too late: %s-%d (run for %d/%d steps so far)\n", time-pData->heap[11]-pData->heap[10], pData->TLN, pData->heap[0], pData->heap[5], pData->heap[1] );
        }
        else{
            printf( "ERROR - Attempting to promote foreground process: %s-%d (run for %d/%d steps so far)\n", pData->TLN, pData->heap[0], pData->heap[5], pData->heap[1] );
        }

    }
}

/* freeProcessData
 * input: void
 * output: void
 *
 * Frees the processData currently loaded in RAM.  Call this after a process has run to completion.
 * Reports errors if it was run the incorrect number of steps.
 */
void freeProcessData( ){
    printf( "Process data deleted: %s-%d (run for %d/%d steps)\n", RAM->TLN, RAM->heap[0], RAM->heap[5], RAM->heap[1] );
    if( RAM->heap[1]>RAM->heap[5] ){
        printf( "ERROR - Process deleted with %d steps left to do: %s-%d\n", RAM->heap[1]-RAM->heap[5], RAM->TLN, RAM->heap[0] );
    }
    if( RAM->heap[5]>RAM->heap[1] ){
        printf( "ERROR - Process run for %d steps more than was required: %s-%d\n", RAM->heap[5]-RAM->heap[1], RAM->TLN, RAM->heap[0]  );
    }
    if( RAM->heap[7] && (time-RAM->heap[11]-RAM->heap[10]>0) )
        printf( "ERROR - Background process was not promoted: %s-%d\n", RAM->TLN, RAM->heap[0] );

    free(RAM);
    RAM = NULL;
}

/************************ Code below this point is internal use only ************************/

/* runProcessForOneTimeStep
 * input: the process name and the process data
 * output: a string
 * FOR INTERNAL USE ONLY
 *
 * Simulates the given process for one time step.
 * If it makes a system call to another process it will return that process's name, otherwise it returns NULL.
 */
char* runProcessForOneTimeStep( char *pName ){
    char *ret = NULL;

    printf( "%4d - Running process: %s-%d\n", time, RAM->TLN, RAM->heap[0] );

    RAM->heap[5]++;
    //printf( "heap[5]: %d\n", pData->heap[5] );
    RAM->heap[6]--;

    if( RAM->heap[6]==0 && RAM->heap[3]>1 ){
        ret = (char *)malloc(21);
        startProcess(ret, RAM);
        RAM->heap[6] = RAM->heap[2];
    }

    time++;
    return ret;
}

/* startProcess
 * FOR INTERNAL USE ONLY
 */
void startProcess( char *pName, processData *pData ){
    char temp[7][4];
    int i;

    if( pData->heap[3]%2==1 && pData->PN21[0]=='F' )
        strcpy(temp[0],"B");
    else if( pData->heap[3]%2==1 && pData->PN21[0]=='B' )
        strcpy(temp[0],"F");
    else{
        temp[0][0] = pData->PN21[0];
        temp[0][1] = '\0';
    }

    strcpy( temp[1], pData->TLN );

    nameNum++;
    sprintf( temp[2], "%d", (nameNum)%100 );
    sprintf( temp[3], "%d", pData->heap[1] );

    sprintf( temp[4], "%d", pData->heap[2] );
    sprintf( temp[5], "%d", max(pData->heap[3]/2,1) );

    sprintf( temp[6], "%d", pData->heap[9] );

    strcpy( pName, "" );
    for( i=0; i<6; i++ ){
        strcat( pName, temp[i] );
        strcat( pName, "|" );
    }
    strcat( pName, temp[i] );
    pData->heap[8]++;
    pData->heap[9]+=pData->heap[1]/pData->heap[2];
}

/* authenticationRAM
 * FOR INTERNAL USE ONLY
 */
bool authenticationRAM( char *pName ){
    if( pName==NULL ){
        fprintf(stderr, "ERROR - Authentication failed - pName is NULL.\n");
        return false;
    }
    else if( RAM == NULL ){
        fprintf(stderr, "ERROR - Authentication failed - data was not loaded into RAM (be sure to call loadProcessData).\n");
        return false;
    }
    else if( RAM->PN21==NULL ){
        fprintf(stderr, "ERROR - Authentication failed - data in RAM may have been corrupted.\n");
        return false;
    }
    else if( strcmp(pName, RAM->PN21) ){
        fprintf(stderr, "ERROR - Authentication failed - incorrect data was loaded into RAM (be sure to call loadProcessData).\n");
        return false;
    }
    return true;
}

/* authentication
 * FOR INTERNAL USE ONLY
 */
bool authentication( char *pName, processData *pData  ){
    if( pName==NULL ){
        fprintf(stderr, "ERROR - Authentication failed - pName is NULL.\n");
        return false;
    }
    else if( pData == NULL ){
        fprintf(stderr, "ERROR - Authentication failed - pData is NULL.\n");
        return false;
    }
    else if( pData->PN21==NULL ){
        fprintf(stderr, "ERROR - Authentication failed - data in pData may have been corrupted.\n");
        return false;
    }
    else if( strcmp(pName, pData->PN21) ){
        fprintf(stderr, "ERROR - Authentication failed - mismatch of data associated with pName and pData.\n");
        return false;
    }
    return true;
}

/* max
 * FOR INTERNAL USE ONLY
 */
int max( int a, int b ){
    if(a>b)
        return a;
    else
        return b;
}

/* powInt
 * FOR INTERNAL USE ONLY
 */
int powInt( int a, int b ){
    int product = 1;
    while( b>0 ){
        product*=a;
        b--;
    }
    return product;
}
