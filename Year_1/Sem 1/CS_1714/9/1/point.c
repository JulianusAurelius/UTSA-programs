#ifndef POINT_C
#define POINT_C
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include"point.h"

void midpoint(Point p1, Point p2, Point* m)
{
    m->x = (p1.x - p2.x) / 2.0 + p2.x;
    m->y = (p1.y - p2.y) / 2.0 + p2.y;
    m->z = (p1.z - p2.z) / 2.0 + p2.z;
}


void distance(Point p1, Point p2, double* d)
{
    double t = pow(p1.x-p2.x, 2) + pow(p1.y-p2.y, 2) + pow(p1.z-p2.z, 2);
    t = pow(t, .5);
    *d = t;
}

#endif
