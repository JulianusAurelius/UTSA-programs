#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef FUNCTIONS_C
#define FUNCTIONS_C
#define LENGTH 5

double average(int arr[])
{
  double avg = 0;
  for (int i = 0; i < LENGTH; ++i)
  {
    avg += arr[i];
  }
  avg /= LENGTH;
  return avg;
}

void quadraticFormula(double a, double b, double c, double* x1, double* x2)
{
  double root = sqrt((pow(b,2) - (4.0 * a * c))) / (2.0 * a);
  double neg_b = (0.0 - b) / (2.0 * a);
  *x1 = neg_b + root;
  *x2 = neg_b - root;
}

#endif
