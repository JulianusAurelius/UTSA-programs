#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size;
    int* myData = NULL;
    scanf("%d", &size);
    
    myData = (int*)malloc(size * sizeof(int));
    
    int i;
    for (i=0; i<size; ++i)
    {
        *(myData+i) = i;
    }
    
    double count;
    for (i=0; i<size; ++i)
    {
        printf("%d ", *(myData+i));
        count += *(myData+i);
    }
    count = count / size;
    printf("\naverage: %.2f\n",count);

    return 0;
}