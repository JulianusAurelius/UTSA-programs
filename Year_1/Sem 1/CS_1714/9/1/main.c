#include<stdio.h>
#include<stdlib.h>
#include"point.h"
#include<math.h>

int main()
{
    Point p1;
    Point p2;
    Point mid;
    double dis;

    scanf("%lf", &p1.x);
    scanf("%lf", &p1.y);
    scanf("%lf", &p1.z);
    scanf("%lf", &p2.x);
    scanf("%lf", &p2.y);
    scanf("%lf", &p2.z);

    midpoint(p1, p2, &mid);
    distance(p1, p2, &dis);

    printf("midpoint: %.2lf, %.2lf, %.2lf\n", mid.x, mid.y, mid.z);
    printf("distance: %.2lf\n", dis);


    return 0;
}
