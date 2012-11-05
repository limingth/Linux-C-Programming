#include <stdio.h>
#include <io.h>        
#include <fcntl.h>     
#include <sys\types.h> 
#include <sys\stat.h>  

void main(void)
 {
    int handle;

    if ((handle = creat("100ZEROS.DAT", S_IWRITE)) == -1)
	 fprintf(stderr, "Error opening 100ZEROS.DAT");
    else
     { 
       if (chsize(handle, 100L)) 
	 printf("Error changing file size\n");
       close(handle);
     }
 }
