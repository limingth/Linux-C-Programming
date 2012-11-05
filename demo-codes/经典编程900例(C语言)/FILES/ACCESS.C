#include <stdio.h>
#include <io.h>

void main (int argc, char *argv[])
 {
   int access_mode;

   access_mode = access(argv[1], 0);
   
   if (access_mode)
     printf("File %s does not exist\n");
   else    
     {
       access_mode = access(argv[1], 2);

       if (access_mode)
         printf("File cannot be written\n");
       else
         printf("File can be written\n");

       access_mode = access(argv[1], 4);

       if (access_mode)
         printf("File cannot be read\n");
       else
         printf("File can be read\n");
       
       access_mode = access(argv[1], 6);

       if (access_mode)
         printf("File cannot be read/write\n");
       else
         printf("File can be read/write\n");
     }
 }
