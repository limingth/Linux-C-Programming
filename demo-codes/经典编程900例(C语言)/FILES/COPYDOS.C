#include <stdio.h>
#include <dos.h>

void main (int argc, char **argv)
  {
    union REGS inregs, outregs;
    struct SREGS segs;

    char buffer[256];

    unsigned source_handle, target_handle;

    if (*argv[1] && *argv[2])
      {
	 // Open the file to copuy
	 inregs.h.ah = 0x3D;
	 inregs.h.al = 0;     // Open for read access
	 inregs.x.dx = (unsigned) argv[1];
	 segread (&segs);
	 intdosx(&inregs, &outregs, &segs);

	 if (outregs.x.cflag)
	   printf ("Error opening source file %s\n", argv[1]);
	 else
	   {
	      source_handle = outregs.x.ax;

	      // Create the target file, truncating an
	      // existing file with the same name
	      inregs.h.ah = 0x3C;
	      inregs.x.cx = 0;     // Open with normal attribute
	      inregs.x.dx = (unsigned) argv[2];
	      intdosx (&inregs, &outregs, &segs);

	      if (outregs.x.cflag) 
		printf ("Error creating target file %s\n", argv[2]);
	      else                  
		{
		   target_handle = outregs.x.ax;
       
		   do {
		     // Read the source data
		     inregs.h.ah = 0x3F;
		     inregs.x.bx = source_handle;
		     inregs.x.cx = sizeof(buffer);
		     inregs.x.dx = (unsigned) buffer;
		     intdosx (&inregs, &outregs, &segs);
		     
		     if (outregs.x.cflag)
		       {
			 printf ("Error reading source file\n");
			 break;
		       }
		     else if (outregs.x.ax)  // Not end of file
		       {           
			 // Write the data                                           
			 inregs.h.ah = 0x40;
			 inregs.x.bx = target_handle;
			 inregs.x.cx = outregs.x.ax;
			 inregs.x.dx = (unsigned) buffer;
			 intdosx (&inregs, &outregs, &segs);
		     
			 if (outregs.x.cflag)
			   {
			     printf ("Error writing target file\n");
			     break;
			   }
		      }
		   } while (outregs.x.ax != 0);

		  // Close the files
		  inregs.h.ah = 0x3E;
		  inregs.x.bx = source_handle;
		  intdos (&inregs, &outregs);
		  inregs.x.bx = target_handle;
		  intdos (&inregs, &outregs);      
		}
	   }         
      }
    else
      printf ("Specify source and target filenames\n"); 
  }
