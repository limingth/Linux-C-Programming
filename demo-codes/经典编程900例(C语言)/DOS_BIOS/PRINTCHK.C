#include <bios.h>
#include <conio.h>
#include <stdio.h>

void main (void)
  {
    int status = 0;
    int old_status = 0;

    do
     {
       status = biosprint(2, 0, 0);  // Read LPT1       
	   
       if (status != old_status)
	 {
	   if (status & 1)
	     printf ("Time-out\t");

	   if (status & 8)
	     printf ("Output Error\t");
 
	   if (status & 16)
	     printf ("Printer Selected\t");
       
	   if (status & 32)
	     printf ("Out of Paper\t");

	   if (status & 64)
	     printf ("Acknowledge\t");

	   if (status & 128)
	     printf ("Printer Not Busy");
	  
	   printf ("\n");
	 
	   old_status = status;
	}
      }
    while (! kbhit());       
  }
