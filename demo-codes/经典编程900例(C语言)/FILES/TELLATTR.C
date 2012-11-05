#include <stdio.h>
#include <dos.h>
#include <io.h>

void main(int argc, char *argv[])
 {
   int attributes;

   if ((attributes = _chmod(argv[1], 0)) == -1)
     printf("Error accessing %s\n", argv[1]);
   else
     {
         if (attributes & FA_ARCH)
           printf("Archive ");

         if (attributes & FA_DIREC)
           printf("Directory ");
         
         if (attributes & FA_HIDDEN)
           printf("Hidden ");
         
         if (attributes & FA_LABEL)
           printf("Volume label ");
         
         if (attributes & FA_RDONLY)
           printf("Readonly ");

         if (attributes & FA_SYSTEM)
           printf("System ");
     }
 }
