#include <stdio.h>
#include <io.h>        
#include <fcntl.h>     
#include <sys\types.h> 
#include <sys\stat.h>  

void main(int argc, char *argv[])
 {
    int source, target; // file handles
    char buffer[1024];  // I/O buffer 
    int bytes_read;     

    if (argc < 3)
	fprintf(stderr, "Must specify source and target files\n");
    else if ((source = open(argv[1], O_BINARY | O_RDONLY)) == -1)
	fprintf(stderr, "Error opening %s\n", argv[1]);
    else if ((target = open(argv[2], O_WRONLY | O_BINARY | O_TRUNC |
	     O_CREAT, S_IWRITE)) == -1)
	 fprintf(stderr, "Error opening %s\n", argv[2]);
    else
      {
	 while (!eof(source))
	  {
	    if ((bytes_read = read(source, buffer, sizeof(buffer))) <= 0)
		fprintf(stderr, "Error reading from source file");
	    else if (write(target, buffer, bytes_read) != bytes_read)
		fprintf(stderr, "Error writing to target file");
	  }

	 close(source);
	 close(target);
     }
 }
