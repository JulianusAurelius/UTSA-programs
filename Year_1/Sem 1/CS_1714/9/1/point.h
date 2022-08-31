#ifndef POINT_H
#define POINT_H

typedef struct Pointer_Struct {
    double x;
    double y;
    double z;
} Point;

void midpoint(Point p1, Point p2, Point* m);
void distance(Point p1, Point p2, double* d);

#endif
