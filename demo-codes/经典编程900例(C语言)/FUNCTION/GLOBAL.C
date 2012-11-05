#include <stdio.h>

int a = 1, b = 2, c = 3;  // Global variables

void global_values(void)
 {
   printf("a contains %d b contains %d c contains %d\n", a, b, c);
 }

void main(void)
 {
   global_values();
   printf("a contains %d b contains %d c contains %d\n", a, b, c);
 }
