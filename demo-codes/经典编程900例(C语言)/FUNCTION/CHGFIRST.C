#include <stdio.h>

void change_first(int *first, int second)
 { 
   *first = second;  // Assign value of second to first
 }

void main(void) 
 {
   int a = 0, b = 5;

   change_first(&a, b);
   printf("Value of a %d value of b %d\n", a, b);
 }

