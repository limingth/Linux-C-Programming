#include <stdio.h>
#include <dos.h>
#include <io.h>

void main(void)
 {
   char path[64] = "C:\\TEMP\\";

   int handle;


   if ((handle = creattemp(path, 0)) == -1)
     printf("Error creating file\n");
   else
    {
      printf("Complete path: %s\n", path);
      close(handle);
    }
 }

