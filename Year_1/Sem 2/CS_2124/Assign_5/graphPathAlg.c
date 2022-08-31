#include "graph.h"
#include "graphPathAlg.h"


/* printNames
 * input: none
 * output: none
 *
 * Prints names of the AWESOME students who worked on this solution
 */
void printNames( )
{
    /* TODO : Fill in you and your partner's names (or N/A if you worked individually) */
    printf("This solution was completed by:\n");
    printf("\e[40m\e[1m\e[36m\e[6mJ\e[37mu\e[36ml\e[37mia\e[36mn\e[37mu\e[36ms\e[37m Au\e[36mr\e[37me\e[36ml\e[37miu\e[36rs\e[0m\n");
    printf("YYY\n");
}

/* OPTIONAL HELPER FUNCTION
 * buildGraph
 *
 * IMPORTANT NOTE: This is an entirely optional helper function which is only called by student implemented functions.
 * Creates a new graph to represent the given maze.  
 */
Graph* buildGraph( array2D* maze /* and other parameters you find helpful */  )
{
    //OPTIONAL TODO: Translate the given maze into a graph.  'X' represents impassable locations.  Only moves of up, down, left, and right are allowed. 
    /* With the right parameters this can be used by all three functions below to build the graph representing their different maze problems. */
    /* HINT 1: To solve this, my solution used the functions createGraph and setEdge from graph.c */
    /* HINT 2: My solution also used createPoint from point2D.c */

    return NULL; /* TODO: Replace with your graph representing maze */
}



/* Recursive */
int traverse(array2D* maze, int x, int y) {
    if (maze->array2D[x][y] == 'F') {
        return 1;
    }
    else if (maze->array2D[x][y] == 'X') {
        return 0;
    }
    else {
        maze->array2D[x][y] = 'X';
        int i = traverse(maze, x, y+1);
        if (i == 1) {
            return 1;
        }
        i = traverse(maze, x+1, y);
        if (i == 1) {
            return 1;
        }
        i = traverse(maze, x-1, y);
        if (i == 1) {
            return 1;
        }
        i = traverse(maze, x, y-1);
        if (i == 1) {
            return 1;
        }
    }
    return 0; // Not needed?
}

/* hasPath
 * input: an array2D pointer to a maze
 * output: pathResult
 *
 * Detects whether a path exists from 'S' to 'F' in the graph. 'X' marks impassable regions.
 */
pathResult hasPath( array2D *maze )
{
    //TODO: Complete this function
    /* HINT 1: To solve this, my solution used the functions createGraph, freeGraph, setEdge, dijkstrasAlg, getDistance from graph.c */
    /* HINT 2: My solution also used createPoint from point2D.c */
    /* HINT 3: You might also consider using the new helper function buildGraph to build the graph representing maze. */
    char start = 'S';
    // Find S
    int startRow = 0;
    int startCol = 0;
    int i;
    int j;
    for ( i = 0; i < maze->length; i++) {
        for ( j = 0; j < maze->width; j++) {
            if (maze->array2D[i][j] == start) {
                startRow = i;
                startCol = j;
                break;
            }
        }
    }
    // printf("\e[31m\e[1m(x,y): (%d,%d): %c\e[0m\n\n\n", startRow, startCol, maze->array2D[startRow][startCol]);
    // Setup for finding F
    array2D* copy = mallocArray2D(maze->length, maze->width);
    // copy 2d array to copy
    for (i = 0; i < maze->length; i++) {
        for ( j = 0; j < maze->width; j++) {
            copy->array2D[i][j] = maze->array2D[i][j];
        }
    }
    int result = traverse(copy, startRow, startCol);
    freeArray2D(copy);

    if (result == 1) {
        return PATH_FOUND;
    }
    else {
        return PATH_IMPOSSIBLE;
    }
    // return PATH_UNKNOWN; /* TODO: Replace with PATH_FOUND or PATH_IMPOSSIBLE based on whether a path exists */
}






/* Recursive */
int counting_traverse(array2D* maze, int x, int y, int depth, int** haveIbeenHere) {//, array2D* copy) {
    // printf("\e[31m\e[1m(x,y): (%d,%d): %c\e[0m\n", x, y, maze->array2D[x][y]);
    // printf("\e[31m\e[1mDepth: %d\e[0m\n\n\n", depth);
    if (maze->array2D[x][y] == 'F') {
        return depth;
    }
    else if (maze->array2D[x][y] == 'X') {
        return 0;
    }
    else if (haveIbeenHere[x][y] == 1) {
        return 0;
    }
    else {
        haveIbeenHere[x][y] = 1;
        // maze->array2D[x][y] = 'X';
        int i = 0;
        int j = 0;
        int k = 0;
        int g = 0;
        i = (y+1) >= maze->width ? 0 : counting_traverse(maze, x, y+1, depth+1, haveIbeenHere);//, copy);
        g = (y-1) < 0 ? 0 : counting_traverse(maze, x, y-1, depth+1, haveIbeenHere);//, copy);
        j = (x+1) >= maze->length ? 0 : counting_traverse(maze, x+1, y, depth+1, haveIbeenHere);//, copy);
        k = (x-1) < 0 ? 0 : counting_traverse(maze, x-1, y, depth+1, haveIbeenHere);//, copy);
        // j = counting_traverse(maze, x+1, y, depth+1);
        // g = counting_traverse(maze, x, y-1, depth+1, haveIbeenHere, copy);
        // k = counting_traverse(maze, x, y-1, depth+1);
        // haveIbeenHere[x][y] = 0; // Moved to inside of if statement to help runtime?
        if ( (i!=0) || (j!=0) || (g!=0) || (k!=0) ) {
            haveIbeenHere[x][y] = 0; // With this here, it creates deadspots where there is no answer. Good for program
            // if ((copy->array2D[x][y] == ' ') || (copy->array2D[x][y] > (depth + 'a'))) {
            //     // copy->array2D[x][y] = depth > 9 ? (depth-10) + 'A' : depth + '0'; 
            //     copy->array2D[x][y] = depth + 'a';
            // }
            // prints i, j, k, g
            // printf("\e[31m\e[1mi: %d, j: %d, k: %d, g: %d\e[0m\n\n", i, j, k, g);
            i = i==0 ? maze->length*maze->width+1 : i;
            j = j==0 ? maze->length*maze->width+1 : j;
            g = g==0 ? maze->length*maze->width+1 : g;
            k = k==0 ? maze->length*maze->width+1 : k;
            if (i<j){
                if (i<g){
                    if (i<k){
                        return i;
                    }
                    else{
                        return k;
                    }
                }
                else{
                    if (g<k){
                        return g;
                    }
                    else{
                        return k;
                    }
                }
            }
            else{
                if (j<g){
                    if (j<k){
                        return j;
                    }
                    else{
                        return k;
                    }
                }
                else{
                    if (g<k){
                        return g;
                    }
                    else{
                        return k;
                    }
                }
            }
        }
    }
    return 0; // Not needed?
}


/* findNearestFinish
 * input: an array2D pointer to a maze, a pointer to an int
 * output: pathResult
 *
 * The maze contains one 'S' and multiple 'F's (1 or more).  'X' marks impassable regions.
 * Find the length of the shortest path to any 'F' from 'S' and return it in spDist.
 * If no 'F' is reachable set spDist to INT_MAX.
 */
pathResult findNearestFinish( array2D *maze, int *spDist )
{
    //TODO: Complete this function
    /* HINT 1: To solve this, my solution used the functions createGraph, freeGraph, setEdge, dijkstrasAlg, getDistance from graph.c */
    /* HINT 2: My solution also used createPoint from point2D.c */
    /* HINT 3: You might also consider using the new helper function buildGraph to build the graph representing maze. */
    if (hasPath(maze) == PATH_FOUND) {
        char start = 'S';
        // Find S
        int startRow = 0;
        int startCol = 0;
        int i;
        int j;
        for (i = 0; i < maze->length; i++) {
            for (j = 0; j < maze->width; j++) {
                if (maze->array2D[i][j] == start) {
                    startRow = i;
                    startCol = j;
                    break;
                }
            }
        }
        // Setup for finding F
        // array2D* copy = mallocArray2D(maze->length, maze->width);
        // for (int i = 0; i < maze->length; i++) {
        //     for (int j = 0; j < maze->width; j++) {
        //         copy->array2D[i][j] = maze->array2D[i][j];
        //     }
        // }
        // printf("\e[31m\e[1m(x,y): (%d,%d): %c\e[0m\n\n\n", startRow, startCol, maze->array2D[startRow][startCol]);
        int** haveIbeenHere = malloc(sizeof(int*) * maze->length);

        for ( i = 0; i < maze->length; i++) {
            haveIbeenHere[i] = malloc(sizeof(int) * maze->width);
            for (j = 0; j < maze->width; j++) {
                haveIbeenHere[i][j] = 0;
            }
        }
        int result = counting_traverse(maze, startRow, startCol, 0, haveIbeenHere);//, copy);
        // copy->array2D[1][3] = 'A';
        //print length and width
        // printf("\e[31m\e[1mLength: %d, Width: %d\e[0m\n", maze->length, maze->width);
        // printArray2D(copy, 1);
        *spDist = result;
        
        for (i = 0; i < maze->length; i++) {
            free(haveIbeenHere[i]);
        }
        free(haveIbeenHere);
        return PATH_FOUND;
    }
    else {
        *spDist = INT_MAX;
        return PATH_IMPOSSIBLE;
    }

    
    // (*spDist) = INT_MAX; /* TODO: This returns your shortest path distance to any 'F' from the 'S'.  Set it to INT_MAX if no path exists. */
    
    // return PATH_UNKNOWN; /* TODO: Replace with PATH_FOUND or PATH_IMPOSSIBLE based on whether a path exists */
}















/* Recursive */
int tunnel_traverse(array2D* maze, int x, int y, int ksLeft, int** haveIbeenHere, int** kListLeft, int flag_m) {
    // printf("start\n");
    // printf("x: %d, y: %d, ksLeft: %d\n", x, y, ksLeft);
    // printf("C: %c\n", maze->array2D[x][y]);
    // printf("haveIbeenHere[x][y]: %d\n", haveIbeenHere[x][y]);
    if (haveIbeenHere[x][y] == 1) {
        // return 0;
        if (kListLeft[x][y] < ksLeft) {
            kListLeft[x][y] = ksLeft;
        }
        else {
            return 0;
        }
    }
    // else {
    //     kListLeft[x][y] = ksLeft;
    // }
    // int flag = 0;
    // if (kListLeft[x][y] < ksLeft) {
    //         kListLeft[x][y] = ksLeft;
    // }
    // if (maze->array2D[x][y] == ' ') {
    //     // printf("\e[31m\e[1m(x,y): (%d,%d): %c\e[0m\n", x, y, maze->array2D[x][y]);
    //     printf("KsLeft: %d\n", ksLeft);
    // }
    if (maze->array2D[x][y] == 'F') {
        return 1;
    }
    else if (maze->array2D[x][y] == 'X') {
        // flag_m = 1;
        // // if (ksLeft == 0 )
        // flag = 1;
        if (ksLeft > 0) {
            // printf("ksLeft: %d, kListLeft: %d\n", ksLeft, kListLeft[x][y]);
            // printf("test2\n");
            ksLeft--;
            // kListLeft[x][y]--;
        }
        else {
            // printf("test3\n");
            return 0;
        }
    }
    // else {
    //     flag_m = 0;
    //     kListLeft[x][y] = ksLeft;
    // }
    // if (flag) {
    //     haveIbeenHere[x][y] = 0;
    // }
    // else {
    //     haveIbeenHere[x][y] = 1;
    // }
    // maze->array2D[x][y] = 'X';
    haveIbeenHere[x][y] = 1;
    int i = 0;
    i = (y+1) >= maze->width ? 0 : tunnel_traverse(maze, x, y+1, ksLeft, haveIbeenHere, kListLeft, flag_m);//, copy);
    if (i == 1) {
        // haveIbeenHere[x][y+1] = 0;
        // haveIbeenHere[x][y] = 0;
        return 1;
    }
    i = (y-1) < 0 ? 0 : tunnel_traverse(maze, x, y-1, ksLeft, haveIbeenHere, kListLeft, flag_m);//, copy);
    if (i == 1) {
        // haveIbeenHere[x][y-1] = 0;
        // haveIbeenHere[x][y] = 0;
        return 1;
    }
    i = (x+1) >= maze->length ? 0 : tunnel_traverse(maze, x+1, y,ksLeft, haveIbeenHere, kListLeft, flag_m);//, copy);
    if (i == 1) {
        // haveIbeenHere[x+1][y] = 0;
        // haveIbeenHere[x][y] = 0;
        return 1;
    }
    i = (x-1) < 0 ? 0 : tunnel_traverse(maze, x-1, y, ksLeft, haveIbeenHere, kListLeft, flag_m);//, copy);
    if (i == 1) {
        // haveIbeenHere[x-1][y] = 0;
        // haveIbeenHere[x][y] = 0;
        return 1;
    }
    // haveIbeenHere[x][y] = 0;
    return 0;
}




/* findTunnelRoute
 * input: an array2D pointer to a maze, an int representing the number X's you can travel through
 * output: pathResult
 *
 * Detects whether a path exists from 'S' to 'F' in the graph where you pass through at most k 'X' symbols.
 */
pathResult findTunnelRoute( array2D *maze, int k )
{
    // return PATH_UNKNOWN;
    // print sizes
    // printf("\e[31m\e[1mSize of maze: (%d,%d)\e[0m\n", maze->length, maze->width);
    //TODO: Complete this function
    /* HINT 1: To solve this, my solution used the functions createGraph, freeGraph, setEdge, dijkstrasAlg, getDistance from graph.c */
    /* HINT 2: My solution also used createPoint from point2D.c */
    /* HINT 3: You might also consider using the new helper function buildGraph to build the graph representing maze. */
    char start = 'S';
    // Find S
    int startRow = 0;
    int startCol = 0;
    int i;
    int j;
    for (i = 0; i < maze->length; i++) {
        for (j = 0; j < maze->width; j++) {
            if (maze->array2D[i][j] == start) {
                startRow = i;
                startCol = j;
                break;
            }
        }
    }
    // Setup for finding F
    // array2D* copy = maze;
    // printf("\e[31m\e[1m(x,y): (%d,%d): %c\e[0m\n\n\n", startRow, startCol, maze->array2D[startRow][startCol]);
    // int** haveIbeenHere = malloc(sizeof(int*) * maze->length);
    // for (int i = 0; i < maze->length; i++) {
    //     haveIbeenHere[i] = malloc(sizeof(int) * maze->width);
    //     for (int j = 0; j < maze->width; j++) {
    //         haveIbeenHere[i][j] = 0;
    //     }
    // }
    array2D* copy = mallocArray2D(maze->length, maze->width);
    for (i = 0; i < maze->length; i++) {
        for (j = 0; j < maze->width; j++) {
            copy->array2D[i][j] = maze->array2D[i][j];
            // if (copy->array2D[i][j] == 'X') {
            //     copy->array2D[i][j] = '\0';
            // }
        }
    }
    int** haveIbeenHere = malloc(sizeof(int*) * maze->length);

    for (i = 0; i < maze->length; i++) {
        haveIbeenHere[i] = malloc(sizeof(int) * maze->width);
        for (j = 0; j < maze->width; j++) {
            haveIbeenHere[i][j] = 0;
        }
    }
    int** kListLeft = malloc(sizeof(int*) * maze->length);
    
    for (i = 0; i < maze->length; i++) {
        kListLeft[i] = malloc(sizeof(int) * maze->width);
        for (j = 0; j < maze->width; j++) {
            kListLeft[i][j] = 0;
        }
    }
    int result = 0;
    result = tunnel_traverse(maze, startRow, startCol, k, haveIbeenHere, kListLeft, 0);
    //print kListLeft
    // printArray2D(maze, 1);
    // printf("Map with tunnel length: %d\n", k);
    // printf("S (x,y): (%d,%d)\n", startRow, startCol);
    // if (result == 0) {
    //     for (int i = 0; i < maze->length; i++) {
    //         for (int j = 0; j < maze->width; j++) {
    //             printf("%3d ", kListLeft[i][j]);
    //         }
    //         printf("\n");
    //     }
    // }
    // printArray2D(copy, 1);
    // printArray2D(maze, 1);
    //verify result
    // printf("\e[31m\e[1mResult: %d\e[0m\n", result);
    for (i = 0; i < maze->length; i++) {
        free(kListLeft[i]);
    }
    free(kListLeft);
    for (i = 0; i < maze->length; i++) {
        free(haveIbeenHere[i]);
    }
    // printf("test\n");
    free(haveIbeenHere);
    freeArray2D(copy);
    // printf("test2\n");
    // for (int i = 0; i < maze->length; i++) {
    //     free(haveIbeenHere[i]);
    // }
    // free(haveIbeenHere);
    if (result == 0) {
        return PATH_IMPOSSIBLE;
    }
    else {
        return PATH_FOUND;
    }


    return PATH_UNKNOWN; /* TODO: Replace with PATH_FOUND or PATH_IMPOSSIBLE based on whether a path exists */
}