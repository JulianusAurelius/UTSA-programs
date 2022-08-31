#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main()
{
    char x = 'A';
    for (int i = 0; i<100; ++i)
    {
        printf("%c\n", x);
        x++;
    }
    return 0;
}