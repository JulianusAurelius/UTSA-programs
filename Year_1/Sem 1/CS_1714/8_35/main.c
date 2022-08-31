#include <stdio.h>
#include <stdlib.h>
#include"functions.h"
#define LENGTH 5

int main(int argc, char *argv[])
{
  int arr[LENGTH];
  int a;
  int b;
  int c;
  double avg;
  double x1;
  double x2;

  for (int i = 0; i < LENGTH; ++i)
  {
    scanf("%d", arr+i);
  }

  scanf(" %d", &a);
  scanf(" %d", &b);
  scanf(" %d", &c);

  avg = average(arr);
  quadraticFormula(a, b, c, &x1, &x2);

  printf("average: %.2lf\nx1: %.2lf\nx2: %.2lf", avg, x1, x2);
  return 0;
}
