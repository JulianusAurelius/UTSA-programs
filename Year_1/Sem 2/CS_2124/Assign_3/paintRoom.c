#include "paintRoom.h"

void recPaintRoom( RoomData room, int row, int col, int distanceFromA, char currletter /* feel free to remove/add any other parameters here*/ );
/* declare any other helper functions here*/

/* printNames
 * input: none
 * output: none
 *
 * Prints names of the students who worked on this solution
 */
void printNames( )
{
    /* TODO : Fill in you and your partner's names (or N/A if you worked individually) */
    printf("\nThis solution was completed by:\n");
    printf("XX\n");
    printf("YY\n\n");
}

/* TODO
 * paintRoom
 * input: the room to process
 * output: N/A
 *
 * This non-recursive function is called by the driver and it makes the initial call to recursive function recPaintRoom.
 */
void paintRoom( RoomData room )
{
    int i, j;
    /* Call any other helper functions (a helper function to find the location of 'A' in room may be handy) */
    for (i = 0; i < room.numrows; i++) /*finds A*/
    {   
        for (j = 0; j < room.numcols; j++)
        {
            if (room.roomArray[i][j] == 'A')
            {
                recPaintRoom(room, i, j, 0, 'A');
                return;
            }
        }
    }

    /* Call your recursive function here */
    //recPaintRoom( room, /* initial row value */, /* initial col value */, /* initial value for distanceFromA */  );
}

/* TODO
 * recPaintRoom
 * input: the room to process, the row and column of the current location being explored, the distance traveled from 'A'
 * output: N/A
 */
void recPaintRoom( RoomData room, int row, int col, int distanceFromA, char currletter /* feel free to remove/add any other parameters here*/ )
{
    /* Base cases: */
    //print all info for debugging
    // printf("%d %d %d %c\n", row, col, distanceFromA, currletter);
    if ( (row < 0) || (col < 0) || (row > room.numrows) || (col > room.numcols) || (room.roomArray[row][col] == '*') || ((room.roomArray[row][col] < currletter) && (room.roomArray[row][col] != ' ')) || (distanceFromA > room.numcols*room.numrows/2) || ((room.roomArray[row][col] == 'Z') && currletter == 'Z') )
    {
        return;
    }
    room.roomArray[row][col] = currletter;

    if (currletter == 'Z')
    {
        currletter--;
    }
    recPaintRoom(room, row, col+1, distanceFromA+1, currletter+1);
    recPaintRoom(room, row+1, col, distanceFromA+1, currletter+1);
    recPaintRoom(room, row, col-1, distanceFromA+1, currletter+1);
    recPaintRoom(room, row-1, col, distanceFromA+1, currletter+1);




    /* Recursive cases: */

}
