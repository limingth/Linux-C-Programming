#include <stdio.h>
#include <dos.h>
#include <io.h>

void main(void)
 {
   int handle;

   if ((handle = creatnew("NEW.DAT", 0)) == -1)
     printf("Error creating NEW.DAT\n");
   else
    { 
      printf("File successfully created\n");
      close(handle);
    }
 }
