#include <stdio.h>
#include <dos.h>  
#include <fcntl.h>

void main(int argc, char *argv[])
{
    struct Date {
      unsigned int day:5;
      unsigned int month:4;
      unsigned int years:7;
    } date;

    struct Time {
      unsigned seconds:5;
      unsigned minutes:6;
      unsigned hours:5;
    } time;
    
    int handle;

    if (_dos_open(argv[1], O_RDONLY, &handle))
	fprintf(stderr, "Error opening source file\n");
    else
     {
	if (_dos_getftime(handle, &date, &time))
	  printf("Error getting date and time stamp\n");
	else
	  printf("%s last modified %02d-%02d-%d %02d:%02d:%02d\n", 
	       argv[1],
	       date.month,          /* month */
	       date.day,            /* day */
	       date.years + 1980,   /* year */
	       time.hours,          /* hours */
	       time.minutes,        /* minutes */
	       time.seconds * 2);   /* seconds */
	_dos_close(handle);
    }
 }
