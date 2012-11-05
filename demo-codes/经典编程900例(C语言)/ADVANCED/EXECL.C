#include <process.h>
#include <stdio.h>

void main(void)
 {
   printf("About to call child process\n\n");
   execl("CHILD.EXE", "CHILD.EXE", 
     "AAA", "BBB", "CCC", NULL);
   printf("\n\nBack from child process--SHOULD NOT APPEAR\n");
 }

