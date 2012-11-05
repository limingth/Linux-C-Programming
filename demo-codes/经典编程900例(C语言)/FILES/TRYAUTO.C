#include <stdio.h>
#include <io.h>
#include <share.h>
#include <fcntl.h>

void main(void)
 {
   int handle;
   int offset = 0;
   int bytes_read;
   char buffer[128];

   if ((handle = sopen("\\AUTOEXEC.BAT", O_BINARY | O_RDONLY, SH_DENYNO)) == -1)
     printf("Error opening AUTOEXEC.BAT\n");
   else
    {
      while (bytes_read = read(handle, buffer, 1)) 
       {   
         if (bytes_read == -1)
           printf("Error reading offset %d\n", offset);
         else
           write(1, buffer, bytes_read);
         offset++;
         lseek(handle, offset, SEEK_SET);
       }
      close(handle);
    }
 }

