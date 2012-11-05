#include <stdio.h>

int a = 1, b = 2, c = 3;  // Global variables

void conflict_a(void)
 {
   int a = 100;

   printf("a contains %d b contains %d c contains %d\n", a, b, c);
 }

void main(void)
 {
   conflict_a();
   printf("a contains %d b contains %d c contains %d\n", a, b, c);
 }
