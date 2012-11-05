#include <stdio.h>
#include <stdlib.h>

void main (void)
 {
   int error;

   for (error = 0; error < sys_nerr; error++)
       printf("Error %d %s\n", error, sys_errlist[error]);
 }

