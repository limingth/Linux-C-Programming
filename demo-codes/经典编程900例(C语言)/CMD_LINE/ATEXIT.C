#include <stdio.h>
#include <stdlib.h>

void first(void)
 {
   printf("First function registered\n");
 }

void second(void)
 {
   printf("Second function registered\n");
 }

void main (void)
 {
   atexit(first);
   atexit(second);
 }


