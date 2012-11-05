#include <stdio.h>

void swap_values(int *, int *);

void main(void)
 {
   int a = 1, b = 2;

   printf("Original values a %d b %d\n", a, b);
   swap_values(a, b);

   printf("Swapped values a %d b %d\n", a, b);
 }

