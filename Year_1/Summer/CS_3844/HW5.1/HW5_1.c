#include <stdio.h>
#include <stdlib.h>

int main() {
    // PROBLEM 3
    int a = 0x55;   // 01010101
    int b = 0x46;   // 01000110
    int ans = a & !b; // logical
    // !b = !(TRUE) = 0x0
    // a & !b = TRUE & FALSE = FALSE = 0x0
    printf("a&!b = %d\n", ans);
    ans = a & ~b; // bitwise
    // 01010101
    // 10111001
    // 00010001 = 0x11 = 17
    printf("a&~b = %d\n", ans);
    // PROBLEM 3


    // PROBLEM 6
    // int i = 0;
    // while (i!=-1) {
    //     int j = 0;
    //     while (j!=-1) {
    //         if (j+i!=(unsigned)j+(unsigned)i) {
    //             printf("%d + %d = %d\n", j, i, j+i);
    //             printf("%d + %d = %d\n", (unsigned)j, (unsigned)i, (unsigned)j+(unsigned)i);
    //         }
    //         j<<=1;
    //         j++;
    //     }
    //     i<<=1;
    //     i++;
    // }
    // printf("done\n");
    // printf("%d\n", -1+-1==(unsigned)(-1)+(unsigned)(-1));
    // printf("%u %u\n", (unsigned)-4,(unsigned)(-5)+(unsigned)(1));
    // PROBLEM 6


    // PROBLEM 7
    // printf("%d\n", 10000.5==(float)(double)10000.5);
    // printf("%d\n", 1.5==(float)(double)1.5);
    // printf("%d\n", 0.0==(float)(double)0.0);
    // PROBLEM 7



    // PROBLEM 13
    // double d = 1.0;
    // int i = 0;
    // for (i=0; i<20; i++) {
    //     d *= 99999999999999999999.0;
    //     printf("%f\n", d);
    // }
    // PROBLEM 13


    return 0;
}