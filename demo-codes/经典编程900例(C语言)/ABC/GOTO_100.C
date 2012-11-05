#include <stdio.h>

void main()
 {
   int count = 1;

   label:
     printf("%d ", count++);
     
     if (count <= 100)
       goto label;
 }
