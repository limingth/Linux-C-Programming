#include <stdio.h>
#include <dos.h>  
#include <fcntl.h>

void main(int argc, char *argv[])
{
    unsigned date, time;
    int handle;

    if (_dos_open(argv[1], O_RDONLY, &handle))
	fprintf(stderr, "Error opening source file\n");
    else
     {
	if (_dos_getftime(handle, &date, &time))
	  printf("Error getting date/time stamp\n");
	else
	  printf("%s last modified %02d-%02d-%d %02d:%02d:%02d\n", 
	       argv[1],
	       (date & 0x1E0) >> 5,  /* month */
	       (date & 0x1F),        /* day */
	       (date >> 9) + 1980,   /* year */
	       (time >> 11),         /* hours */
	       (time & 0x7E0) >> 5,  /* minutes */
	       (time & 0x1F) * 2);   /* seconds */
	_dos_close(handle);
	}
}
