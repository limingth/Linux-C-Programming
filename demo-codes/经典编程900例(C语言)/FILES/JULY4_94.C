#include <stdio.h>
#include <dos.h>  
#include <fcntl.h>

void main(int argc, char *argv[])
{
    union {
      struct Date {
	unsigned int day:5;
	unsigned int month:4;
	unsigned int years:7;
      } bits;
      unsigned value;
    } date;

    union {
      struct Time {
	unsigned seconds:5;
	unsigned minutes:6;
	unsigned hours:5;
      } bits;
      unsigned value;
    } time;
    
    int handle;

    if (_dos_open(argv[1], O_RDONLY, &handle))
	fprintf(stderr, "Error opening source file\n");
    else
     {
	date.bits.day = 4;
	date.bits.month = 7;
	date.bits.years = 14;  // 1980 + 14
	time.bits.hours = 12;
	time.bits.minutes = 0;
	time.bits.seconds = 0;

	if (_dos_setftime(handle, date.value, time.value))
	  printf("Error setting date/time stamp\n");

	_dos_close(handle);
     }
}
