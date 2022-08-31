#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{                 //3.33333325386047363281
    long double x = 1.000000000000001;
    long double y = x;

    unsigned long long int i = 1.5 * pow(10, 5);
    unsigned long long int p = 0;
    unsigned long long int numOfResets = 0;

    for (p=0; p<i; p++)
    {
        x *= x;
        printf("p: %lld with %Lf and %lld resets when at %.15Lf%%\n", p, x, numOfResets, (y-1)*100);
        if (x > 2.0)
        {
            numOfResets++;
            x = y;
        }
    }
    return 0;
}