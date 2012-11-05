#include <stdio.h>
#include <utime.h>

void main(int argc, char **argv)
 {
   if (utime(argv[1], (struct utimbuf *) NULL))
     printf("Error setting date and time\n");
   else
     printf("Date and time stamp set\n");
 }

