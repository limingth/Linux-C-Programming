#include <stdio.h>
#include <time.h>
#include <dos.h>

void main (void)
 {
   char buffer[256];

   char key_pressed = 0;
     
   long int counter = 1;

   union REGS inregs, outregs;

   time_t start_time, current_time, end_time; 

   while (fgets(buffer, sizeof(buffer), stdin))
     {
       fputs (buffer, stdout);

       if ((++counter % 25) == 0)
	 {
	   time (&start_time);

	   end_time = start_time + 15;
	
	   do
	     {
	       key_pressed = 0;
	       time (&current_time);
		     
	       inregs.h.ah = 1;
	       int86 (0x16, &inregs, &outregs); 
		
	       if ((outregs.x.flags & 64) == 0)
		 {                 
		    key_pressed = 1;
		    do {                    
		      inregs.h.ah = 0;
		      int86 (0x16, &inregs, &outregs);
		      inregs.h.ah = 1;
		      int86 (0x16, &inregs, &outregs);
		    } while (! (outregs.x.flags & 64)); 
		 } 
	     }            
	   while ((current_time != end_time) && (! key_pressed));  
	 }
     }
  }
