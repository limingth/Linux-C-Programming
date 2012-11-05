#include <stdio.h>
#include <io.h>

void main(void)
 {
   dup2(2, 1);  // stdout is handle 1 stderr is handle 2

   printf("This message cannot be redircted!\n");
 }

