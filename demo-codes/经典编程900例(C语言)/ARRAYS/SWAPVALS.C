#include <stdio.h>

void swap_values(int *a, int *b)
 { 
   int temp;

   temp = *a;  // Temporarily hold the value pointed to by a
   *a = *b;    // Assign b's value to a
   *b = temp;  // Assign a's value to b
 }

void main(void)
 {
   int one = 1, two = 2;

   swap_values(&one, &two);

   printf("one contains %d two contains %d\n", one, two);
 }


   
