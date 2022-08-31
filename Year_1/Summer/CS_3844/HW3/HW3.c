#include <stdio.h>
#include <stdlib.h>

/* Determine whether arguments can be added without overflow */
int uadd_ok(unsigned x, unsigned y)
{
    unsigned max = 0;
    max = ~max; // turn 0000 -> 1111, and since it's unsigned, it makes it the max value
    // printf("%u\n", max);
    return (max - x >= y);
}

/* Determine whether arguments can be added without overflow */
int tadd_ok(int x, int y)
{
    int j;
    int max = 0;
    for (j=0; j<sizeof(int)-1; j++)
    {
        max = max << 8;
        max += 255;
        // printf("%d\n", max);
    }
    max = max << 7;
    max += 127;
    // OR
    // max = pow(2, sizeof(int)*8-1) - 1;
    // if compiled with math.h and -lm
    // printf("%d\n", max);
    if (x >= 0 && y >= 0)
    {
        return (max - x >= y);
    }
    else if (x < 0 && y < 0)
    {
        return (((max + x) + 1) + y >= 0); //used 1s to avoid fringe case overflow during arithmetic
    }
    return 1; //if one is negative and the other is positive, there is no way for it to overflow as long
        // as they are properly added
}

int main() {
    uadd_ok(0, 0);
    tadd_ok(0, 1);
}