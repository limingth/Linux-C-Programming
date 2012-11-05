#include <stdio.h>
#include <dos.h>    
#include <fcntl.h>  
void main(int argc, char *argv[])
{
   char buffer[1024];

   int input, output;                   /* file handles */
   unsigned bytes_read, bytes_written;  /* actual number of bytes transferred */

   if (argc < 3)
     fprintf(stderr, "Must specify source and target file\n");
   else if (_dos_open (argv[1], O_RDONLY, &input))
     fprintf(stderr, "Error opening source file\n");
   else if (_dos_creat (argv[2], 0, &output))
     fprintf(stderr, "Error opening target file\n");
   else
    {
       while (!_dos_read(input, buffer, sizeof(buffer), &bytes_read))
	 {
	   if (bytes_read == 0)
	       break;
	   _dos_write(output, buffer, bytes_read, &bytes_written);
	 }

       _dos_close(input);
       _dos_close(output);
    }
}
