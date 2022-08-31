#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// #include<math.h>

void printPasswords(char* arr, int len, int max);
//void printAllPasswordsAtNLength(int max, int numOfletters, char* letters, int iter, int depth, char** password, int x);
// void printPasswords(int m, char** arr,int n, char* ans, int depth, int);
// void printPasswords(int max, int numOfletters, char* letters);
// void recursivePrintAllPosiblePasswords(int max, int numOfletters, char* letters, int iter, int depth, char** password, int x);
// int powerFactorial(int n, int power);


int main(int argc, char *argv[])
{
    int numOfletters;
    numOfletters = atoi(argv[1]);
    char* letters;
    letters = (char*)malloc(numOfletters*sizeof(char));
    // letters = (char*)malloc(numOfletters * sizeof(char));
    int i;
    for (i = 0; i < numOfletters; i++)
    {
        //letters[i] = (char*)malloc(sizeof(char));
        //strcpy(letters[i], argv[i + 2]);
        letters[i] = argv[i + 2][0];
        //printf("%c\n", letters[i]);
    }
    int max;
    max = atoi(argv[numOfletters + 2]);
    //char* ans;
    //ans = (char*)malloc(max * sizeof(char));
    // printPasswords(max, letters, numOfletters, ans, 0, 0);
    //printf("%s\n", letters);
    printPasswords(letters, numOfletters, max);
    free(letters);
    return 0;
}

void printAllPasswordsAtNLength(int max, char* letters, int i, char* tmp)
{
    if (strlen(tmp) == max) //strlen(tmp))
    {
        printf("%s\n", tmp);
        return;
    }
    else
    {
        //printf("HELLO\n%d\n", i);
        int j;
        for (j = 0; j < strlen(letters); j++)
        {
            //printf("%ld\n\n", strlen(tmp));
            tmp[i] = letters[j];
            printAllPasswordsAtNLength(max, letters, i + 1, tmp);
        }
        tmp[i] = '\0';
        return;
    }
}

void printPasswords(char* arr, int len, int max)
{
    char* tmp;
    tmp = (char*)malloc((max+1) * sizeof(char));
    //Calls helper function printAllPasswordsAtNLength
    int i;
    for (i = 0; i <= max; i++)
    {
        printAllPasswordsAtNLength(i, arr, 0, tmp);
    }
    
}














// void printPasswords(int m, char** arr,int n, char* ans, int depth, int bool)
// {
//     //if max allowed length of string is 0, return
//     if(n==0){
//         return;
//     }
//     if (depth == m)
//     {
//         printf("%s\n", ans);
//         return;
//     }
//     //Each level of recursion prints out the possibilities of the next letter, then calls the next level of recursion
//     int i;
//     for (i = 0; i < n; i++)
//     {
//         ans[depth] = arr[i][0];
//         printf("%s\n", ans);
//         if (bool)
//         {
//             for (int j = 0; j < n; j++)
//             {
//                 printPasswords(m, arr, n, ans, depth + 1, 0);
//             }
//         }
//         else
//         {
//             return;
//         }
//     }

// }




// void printPasswords(int max, int numOfletters, char* letters)
// {
//     int size = powerFactorial(numOfletters, max);
//     char password[size][max+1];
//     //char password[max+1];
//     int i;
//     for (i = 0; i < size; i++)
//     {
//         int j;
//         for (j = 0; j < max; j++)
//         {
//             password[i][j] = '\0';
//         }
//     }
    
//     recursivePrintAllPosiblePasswords(max, numOfletters, letters, 0, 0, password, 1);
//     for (i = 0; i < size; i++)
//     {
//         printf("%s\n", password[i]);
//     }
// }

// int powerFactorial(int n, int power)
// {
//     if (power == 0)
//     {
//         return 0;
//     }
//     else
//     {
//         printf("Test\n\n");
//         return (int)pow((double)n, (double)power) + powerFactorial(n, power - 1);
//     }
// }

// /*
// Need 3 things
// a thing to say how many times it has been passed through, starting at 1 and increasing towards max, passed as the second to next rec
// a thing that counts depth to allow level 1 to print (taken by the first thing)

// DEPTH IS REAL DEPTH, X IS WHICH IS BEING PRINTED
// */
// void recursivePrintAllPosiblePasswords(int max, int numOfletters, char* letters, int iter, int depth, char** password, int x)
// {
//     int j;
//     for (j = iter; j < max-1; ++j)
//     {
//         if (depth == max)
//         {
//             return;
//         }
//         else
//         {
//             int i;
//             for (i = 0; i < numOfletters; i++)
//             {
//                 char temp[max+1];
//                 temp[depth] = letters[i];
//                 if (x == 1)
//                 {
//                     strcat(password[depth+x-1], temp);
//                 }
//                 else
//                 {
//                     recursivePrintAllPosiblePasswords(max, numOfletters, letters, iter, depth + 1, password, x - 1 );
//                 }
//                 password[depth] = '\0';
//             }
//         }
//         ++x;
//     }
// }
