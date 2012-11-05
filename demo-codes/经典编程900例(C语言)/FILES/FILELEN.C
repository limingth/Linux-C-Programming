#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>

void main (int argc, char *argv[])
 {
   int file_handle;

   long file_size;

   if ((file_handle = open(argv[1], O_RDONLY)) == -1)
     printf("Error opening the file %d\n", argv[1]);
   else
     {
       file_size = filelength(file_handle);
       printf("The file size in bytes is %ld\n", file_size);
       close(file_handle);
     }
 }
