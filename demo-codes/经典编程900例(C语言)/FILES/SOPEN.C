#include <stdio.h>
#include <share.h>
#include <io.h>
#include <fcntl.h>

void main(int argc, char *argv[])
 {
   int handle, bytes_read;

   char buffer[256];

   if ((handle = sopen(argv[1], O_RDONLY, SH_DENYWR)) == -1)
     printf("Error opening the file %s\n", argv[1]);
   else
     {
       printf("Press Enter to continue\n");
       getchar();
       
       while (bytes_read = read(handle, buffer, sizeof(buffer)))
         write(1, buffer, bytes_read);  // 1 is stdout
       
       close(handle);
    }
 }
