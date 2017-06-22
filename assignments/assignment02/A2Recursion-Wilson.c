#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* function prototypes */
int min(int x, int y);
int iterGCD(int x, int y);
int recGCD(int x, int y);

int main(void) {
  int num_vals = 6;
  int x_vals[] = {3, 9, 12, 36, 1, 105};
  int y_vals[] = {3, 21, 18, 27, 12, 91};
  int i = 0;

  printf("Assignment 2 Problem 2 by Kevin Wilson.\n");
  printf("---------------------------------------\n\n");

  while (i<num_vals) {
    printf("Iterative GCD: x = %d, y = %d, result = %d\n", x_vals[i], y_vals[i], iterGCD(x_vals[i],y_vals[i]));
    printf("Recursive GCD: x = %d, y = %d, result = %d\n\n", x_vals[i], y_vals[i], recGCD(x_vals[i],y_vals[i]));

    i++;
  }

  return 0;
}

int min(int x, int y) {
  return (x <= y ? x : y);
}

int iterGCD(int x, int y) {
  int minimum = min(x, y);
  int val = minimum;
  while (val > 1 && (x % val != 0 || y % val != 0))
    val--;

  return val;
}

int recGCD(int x, int y) {
  if (y <= x && x % y == 0)
    return y;
  else if (x < y)
    return recGCD(y, x);
  else
    return recGCD(y, x % y);
}
