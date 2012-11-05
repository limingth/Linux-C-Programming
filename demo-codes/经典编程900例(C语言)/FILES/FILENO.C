#include <stdio.h>
#include <io.h>

void main (int argc, char *argv[])
 {
   FILE *stream;

   int handle;

   long file_length;

   if (stream = fopen(argv[1], "r"))
     {
        // Some statements
        handle = fileno(stream);
        file_length = filelength(handle);
        printf("The file length is %ld\n", file_length);
        fclose(stream);
     }
   else
     printf("Error opening %s\n", argv[1]);
 }
