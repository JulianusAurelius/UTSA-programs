#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "queue.h"
#include "multilevelQueueScheduler.h"
#include "processSimulator.h"

void testFile( const char dataFile[], char *(*f)( char *));

int getRuntime(char* processName);
priority getPriority(char* processName);

int main( int argc, char *argv[] )
{
    int i = 0;
    char *testData[] = {"F|NEW|00|12|10|04|00",
                        "B|LNG|00|10|07|03|00",
                        "F|SMP|00|30|08|31|00",
                        "F|RPD|00|09|03|32|00",
                        "F|VID|00|40|99|01|00"};

    schedule *ps = createSchedule();
    char *name;

    //Call addNewProcessToSchedule for all of the starting processes
    for( i=0; i<5; i++){
        char *temp = (char *)malloc(strlen(testData[i])+1);
        strcpy( temp, testData[i] );
        addNewProcessToSchedule( ps, temp, getPriority(temp) );
    }
    printf( "\n" );

    //Simulate time steps until the schedule is finished (i.e. all work finished for all processes)
    while( isScheduleUnfinished( ps ) ){
        name = runNextProcessInSchedule( ps );
        if( name!= NULL )
            addNewProcessToSchedule( ps, name, getPriority(name) );
        printf( "\n" );
    }
    freeSchedule( ps );

    return 0;
}

int getRuntime(char* processName){
    char runtimeString[3];
    int runtime;
    int p = abs((int)getPriority(processName)-1);
    //Read runtime from the 4th |-separated value in the string
    sscanf(processName, "%*[^|]|%*[^|]|%*[^|]|%[^|]", runtimeString);
    sscanf(runtimeString, "%d", &runtime);

    return max(runtime/powInt(2,p),1);
}

priority getPriority(char* processName){
    char priorityString[2];
    priority p;
    //Read runtime from the 1st |-separated value in the string
    sscanf(processName, "%1[^|]", priorityString);
    if( !strcmp(priorityString, "F") )
        p = FOREGROUND;
    else if( !strcmp(priorityString, "B") )
        p = BACKGROUND;
    else{
        fprintf(stderr, "invalid priority\n");
        exit(-1);
    }

    return p;
}
