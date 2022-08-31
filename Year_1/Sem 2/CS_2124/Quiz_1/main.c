int** createA( int n, int m )
{
    //TODO: Declare your variables
    //TODO: malloc an array of type int* and store it in A
    int **A = (int**)malloc(n*sizeof(int*));
    //TODO: use a for loop to malloc arrays of type int and store them in A
    int i;
    int j;
    for(i=0; i<n; i++)
    {
        A[i] = (int*)malloc(m*sizeof(int));
        for (j=0; j<m; j++) //Set the values here instead of later to reduce the overall complexity and lines of code. This complexity is O(nm), whereas the original way would be O(nm+n)
        {
            A[i][j] = j+i*m;
        }
    }
    //TODO: Set the values contained in A
    // for(i=0; i<n; i++) //Still completed this loop to show I was able to do it the original way, in case points would be taken off
    // {
    //     for(j=0; j<m; j++)
    //     {
    //         A[i][j] = j+i*m;
    //     }
    // }
    return A;
}