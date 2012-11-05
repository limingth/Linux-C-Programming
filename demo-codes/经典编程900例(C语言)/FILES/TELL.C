#include <stdio.h>
#include <io.h>
#include <fcntl.h>

void main(void)
 {
   int handle;
   char buffer[512];
   int bytes_read;

   if ((handle = open("\\CONFIG.SYS", O_RDONLY)) == -1)
     printf("Error opening \\CONFIG.SYS\n");
   else
     {
       printf("Current file position %ld\n", tell(handle));

       while (bytes_read = read(handle, buffer, sizeof(buffer)))
         write(1, buffer, bytes_read);

       printf("Current file position %ld\n", tell(handle));
       close(handle);      
     }
 }
 
