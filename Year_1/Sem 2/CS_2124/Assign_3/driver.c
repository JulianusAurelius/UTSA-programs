#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "paintRoom.h"

RoomData read2DArray( const char* name );
void print2DArray( RoomData room );
void free2DArray( RoomData room );

/* change the following constants to add/remove some cases for testing */
const int numFiles = 8;
const char *defaultFilenames[] = { "room-Small01.txt", "room-Small02.txt", "room-Medium01.txt", "room-Medium02.txt", "room-Long01.txt", "room-Long02.txt", "room-Large01.txt", "room-Large02.txt" };
const bool enableFilenames[]   = { true              , true              , true               , true               , true             , true             , true              , true               };


/* DO NOT MODIFY THIS FILE */

int main( int argc, char *argv[] )
{
    int i;
    RoomData room;
    
    printNames( );

    printf("Running default test files: \n\n");

    for( i=0; i<numFiles; i++ )
    {
        if( enableFilenames[i] )
        {
            printf("\n--------------- START OF OUTPUT FOR %s -----------------\n\n", defaultFilenames[i]);

            room = read2DArray( defaultFilenames[i] );
            printf("Base room: \n\n");
            print2DArray( room );

            paintRoom( room );

            printf("\nRoom after algorithm: \n\n");
            print2DArray( room );

            free2DArray( room );

            printf("\n--------------- END OF OUTPUT FOR %s -----------------\n\n", defaultFilenames[i]);
        }
    }

    return 0;
}

//Read in and return room from given file
RoomData read2DArray( const char* name )
{
    int i, j;
    FILE *f = fopen( name, "r" );
    char buffer[100];
    char* line;
    RoomData room;

    if( f==NULL || fgets(buffer, 100, f)==NULL || sscanf( buffer, "%d%d", &room.numrows, &room.numcols )!=2 )
    {
        printf("ERROR - Invalid file format %s\n", name);
        exit(-1);
    }

    line = (char*)malloc( sizeof(char)*(room.numcols+10) );

    room.roomArray = (char**)malloc( sizeof(char*)*(room.numrows) );
    for( i=0; i<room.numrows; i++ )
    {
        room.roomArray[i] = (char*)malloc( sizeof(char)*(room.numcols) );

        if( fgets( line, room.numcols+10, f ) == NULL )
        {
            printf("ERROR - Failed to read %dth row\n", i+1);
            exit(-1);
        }
        for( j=0; j<room.numcols; j++ )
            room.roomArray[i][j] = line[j];
    }

    free(line);

    /* close file and return created trafficData */
    fclose( f );
    return room;
}

//Print given 2D array
void print2DArray( RoomData room )
{
    int i, j;

    for( i=0; i<room.numrows; i++ )
    {
        for( j=0; j<room.numcols; j++ )
            printf("%c", room.roomArray[i][j]);
        printf("\n");
    }
}

//Free given 2D array
void free2DArray( RoomData room )
{
    int i;

    for( i=0; i<room.numrows; i++ )
        free(room.roomArray[i]);
    free(room.roomArray);
}
