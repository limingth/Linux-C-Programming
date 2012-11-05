#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <stdlib.h>

void main(void)
 {
   int output;

   int old_setting;

   old_setting = umask(S_IWRITE);

   if ((output = creat("OUTPUT.DAT", S_IWRITE)) == -1)
     { 
       fprintf(stderr, "Error creating OUTPUT.DAT\n");
       exit(1);
     }
   else
     {
       if (write(output, "Test", 4) == -1)
         fprintf(stderr, "Cannot write to file opened for write access\n");
       else
         printf("File successfully written to\n");
       
       close(output);
     }

   if ((output = open("OUTPUT.DAT", O_WRONLY)) == -1)
     fprintf(stderr, "Error opening OUTPUT.DAT for output\n");
   else     
     printf("File successfully opened for write access\n");
 }
