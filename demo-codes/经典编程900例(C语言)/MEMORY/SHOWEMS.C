#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>

int check_for_ems(void)
  {
     union REGS inregs, outregs;
     struct SREGS segs;
 
     int major, minor;   // DOS version

     struct DeviceHeader {
       struct DeviceHeader far *link;
       unsigned attributes;
       unsigned strategy_offset;
       unsigned interrupt_offset;
       char name_or_number_of_units[8];
     } far *dev;

     int i;

     char driver_name[9];

     // Get the DOS version
     inregs.x.ax = 0x3001;
     intdos (&inregs, &outregs);
     major = outregs.h.al;
     minor = outregs.h.ah;

     if (major < 2)
       return(0);     // Requires DOS 2.0
     else
       {
	 // Get the list of lists
	 inregs.h.ah = 0x52;
	 intdosx (&inregs, &outregs, &segs);

	 if (major == 2)
	   dev = (struct DeviceHeader far *) 
	     MK_FP(segs.es + 1, outregs.x.bx + 7);        
	 else if ((major == 3) && (minor == 0))
	   dev = (struct DeviceHeader far *)
	     MK_FP(segs.es + 2, outregs.x.bx + 8);
	 else
	   dev = (struct DeviceHeader far *)  
	     MK_FP(segs.es + 2, outregs.x.bx + 2);

	 while (FP_OFF(dev) != 0xFFFF)
	   {
	      if (dev->attributes & 0x8000)
		{  // Character device
		  for (i = 0; i < 8; i++)
		    driver_name[i] = dev->name_or_number_of_units[i];
		  driver_name[8] = NULL;       
		}
	  
	      if (! strcmp(driver_name, "EMMXXXX0"))
		return(1);   // Found driver
   
	      dev = dev->link; 
	   }
       }

  return(0);
}

void main (void)
  {
    union REGS inregs, outregs;
    struct SREGS segs;

    unsigned handle;
    unsigned page;
    unsigned index, page_number; 

    unsigned page_frame_address;

    char far *data;

    if (check_for_ems())
      {
	inregs.h.ah = 0x40;
	int86 (0x67, &inregs, &outregs);

	// Make sure EMS is functional
	if (outregs.h.ah == 0)         
	  {
	    // Allocate a handle for 5 pages
	    inregs.h.ah = 0x43;
	    inregs.x.bx = 5;
	    int86 (0x67, &inregs, &outregs);

	    if (outregs.h.ah == 0)
	      {  
		 handle = outregs.x.dx; 

		 // Get the page frame address
		 inregs.h.ah = 0x41;
		 int86 (0x67, &inregs, &outregs);
		 
		 if (outregs.h.ah == 0)
		   {                 
		     page_frame_address = outregs.x.bx;

		     // map the first 4 pages
		     for (page_number = 0; page_number < 4; page_number++)
		       {
			  inregs.h.ah = 0x44;
			  inregs.h.al = page_number;  // Physical page
			  inregs.x.bx = page_number;  // Logical page
			  inregs.x.dx = handle;

			  int86 (0x67, &inregs, &outregs);
 
			  if (outregs.h.ah != 0)
			    {
			       printf ("Error mapping pages %xH\n",
				 outregs.h.ah);

			       // Release the handle
			       inregs.h.ah = 0x45;
			       inregs.x.dx = handle;
			       int86 (0x67, &inregs, &outregs);            
			       exit(0); 
			    } 
		       }        
		     // Fill the first four pages
		     data = (char far *) MK_FP(page_frame_address, 0);
	    
		     for (index = 0; index < 16384; index++)
		       data[index] = 'A';

		     for (index = 16384; index < 32768; index++)
		       data[index] = 'B';

		     for (index = 32768; index < 49152; index++)
		       data[index] = 'C';

		     for (index = 49152; index != 0; index++)
		       data[index] = 'D';

		     // Map logical page 4 into physical page 1
		     inregs.h.ah = 0x44;
		     inregs.h.al = 1;  // Physical page
		     inregs.x.bx = 4;  // Logical page
		     inregs.x.dx = handle;

		     int86 (0x67, &inregs, &outregs);
 
		     if (outregs.h.ah != 0)
		       {
			  printf ("Error mapping page %xH\n",
			    outregs.h.ah);

			  // Release the handle
			  inregs.h.ah = 0x45;
			  inregs.x.dx = handle;
			  int86 (0x67, &inregs, &outregs);            
			  exit(0); 
		       } 

		     // Fill page 4 which resides in page 1
		     for (index = 16384; index < 32768; index++)
		       data[index] = 'E';
		      
		     // Display the first 20 bytes of each page
		     printf ("Physical Page Zero\n");
		     for (index = 0; index < 20; index++)
		       printf ("%c ", data[index]);

		     printf ("\nPhysical Page One\n");
		     for (index = 16384; index < 16404; index++)
		       printf ("%c ", data[index]);

		     printf ("\nPhysical Page Two\n");
		     for (index = 32768; index < 32788; index++)
		       printf ("%c ", data[index]);

		     printf ("\nPhysical Page Three\n");
		     for (index = 49152; index < 49172; index++)
		       printf ("%c ", data[index]);

		     // Map logical page 1 into physical page 3
		     inregs.h.ah = 0x44;
		     inregs.h.al = 3;  // Physical page
		     inregs.x.bx = 1;  // Logical page
		     inregs.x.dx = handle;

		     int86 (0x67, &inregs, &outregs);
 
		     if (outregs.h.ah != 0)
		       {
			  printf ("Error mapping page %xH\n",
			    outregs.h.ah);

			  // Release the handle
			  inregs.h.ah = 0x45;
			  inregs.x.dx = handle;
			  int86 (0x67, &inregs, &outregs);            
			  exit(0); 
		       } 

		     printf ("\nMapping logical page 1 to physical page 3"); 
		     printf ("\nPhysical Page Three\n");
		     for (index = 49152; index < 49162; index++)
		       printf ("%c ", data[index]);

		   }
		 else
		   printf ("Error getting base address %xH\n",
		     outregs.h.ah);
				  
		 // Release the handle
		 inregs.h.ah = 0x45;
		 inregs.x.dx = handle;
		 int86 (0x67, &inregs, &outregs);            
	      }
	    else
	      printf ("Error allocating 5 pages %xH\n", 
		outregs.h.ah); 
	  }
	else 
	 printf ("EMM not functional\n");
      }
    else
      printf ("EMS driver not present\n");

  }


