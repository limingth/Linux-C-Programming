#include <stdio.h>

void local_values(void)
 {
   int a = 1, b = 2, c = 3;

   printf("a contains %d b contains %d c contains %d\n", a, b, c);
 }

void main(void)
 {
   printf("a contains %d b contains %d c contains %d\n", a, b, c);
 }
