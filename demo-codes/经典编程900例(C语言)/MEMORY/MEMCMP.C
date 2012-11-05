#include <stdio.h>
#include <mem.h>

void main(void)
 {
   char *a = "AAA";
   char *b = "BBB";
   char *c = "aaa";

   printf("Comparing %s and %s with memcmp %d\n",
     a, b, memcmp(a, b, sizeof(a)));

   printf("Comparing %s and %s with memicmp %d\n",
     a, b, memicmp(a, c, sizeof(a)));
 }  
 
