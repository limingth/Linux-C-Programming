#include <stdio.h>
#include <dos.h>

void main (void)
  {
     char buffer[256];

     long row_count = 0;

     union REGS inregs, outregs;

     int ctrl_key_pressed, scancode;

     while (fgets (buffer, sizeof(buffer), stdin))
       {
         fputs (buffer, stdout);
            
         if ((++row_count % 24) == 0)
           {
	     printf ("-- More --");
             // get the scancode of the key pressed
	     inregs.h.ah = 0; 
	     int86 (0x16, &inregs, &outregs);
             scancode = outregs.h.ah;

	     // get keyboard state in case of Ctrl-C	
	     ctrl_key_pressed = 0;
	     inregs.h.ah = 2;
             int86 (0x16, &inregs, &outregs);
	
             // Ctrl key flag is bit 2 	
	     ctrl_key_pressed = (outregs.h.al & 4);	

	     // scancode for C is 0x2E	
	     if ((ctrl_key_pressed) && (scancode == 0x2E))
		break;     // Ctrl-C pressed
             printf ("\r");                           
           }
        }
}
