#include <stdlib.h>
#include <stdio.h>
#include <dos.h>

void main (void)
 {
   int i;

   for (i = 0; environ[i]; i++)
     printf("%s\n", environ[i]);
 }

