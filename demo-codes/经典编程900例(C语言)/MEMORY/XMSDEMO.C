#include <stdio.h>
#include <dos.h>
#include <string.h>

// Note: If you want to use XMS function 0xB, this simple 
// xms_access routine only works for tiny, small, or medium 
// models where the value of the data segment does not change.

void xms_access (union REGS *inregs, union REGS *outregs)
  {
     union REGS in, out;
     struct SREGS segs;

     unsigned segs_ds, save_bx;
     unsigned flags;

     void far (*xms)(void);  // pointer to the XMS services

     // Get the entry point to the XMS services
     in.x.ax = 0x4310;
     int86x (0x2F, &in, &out, &segs);

     xms = (void far *) (((long) (segs.es) << 16) + out.x.bx);

     // Assign the input registers to the actual registers
 
     _AX = inregs->x.ax;
     _CX = inregs->x.cx;
     _DX = inregs->x.dx;
     _SI = inregs->x.si;
     _DI = inregs->x.di;    
     _BX = inregs->x.bx;

    xms();   // Call the XMS entry point.

    // Assign the registers to the output register structure  
    asm {     
      pushf
      push bx

      pop save_bx
      pop flags
    }

    outregs->x.ax = _AX;
    outregs->x.bx = save_bx;
    outregs->x.cx = _CX;
    outregs->x.dx = _DX;
    outregs->x.si = _SI;
    outregs->x.di = _DI;

    outregs->x.cflag = flags & 1;
    outregs->x.flags = flags;
  }


void main (void)
  {
    union REGS inregs, outregs;
    struct SREGS segs;

    FILE *data;

    char data_buffer[256];

    struct xms_move {
     long byte_count;         // Number of bytes to move
     unsigned source_handle;  // Data to move
     long source_offset;           
     unsigned destination_handle;  
     long destination_offset;
    } block; 

    unsigned handle;

    int string_length;
    long character_count = 0L;
    int transfer_error = 0;   // 1 if a transfer error occurs  
    int i, extra_byte;

    void xms_access (union REGS *, union REGS *); 
	
    inregs.x.ax = 0x4300;
    int86 (0x2F, &inregs, &outregs);

    if (outregs.h.al != 0x80)
      printf ("XMS driver not installed\n");
    else
      {
	 // Allocate the extended memory 
	 inregs.h.ah = 9;
	 inregs.x.dx = 64;  // Size 64Kb

	 xms_access (&inregs, &outregs);         

	 if (outregs.x.ax == 0)
	   printf ("Error allocating extended memory %2xH\n",
	     outregs.h.bl);
	 else
	   {
	     handle = outregs.x.dx;

	     // Read the file into a conventional memory
	     // buffer and then move the data to extended memory
 
	     if ((data = fopen ("\\AUTOEXEC.BAT", "r")) == NULL)
	       printf ("Error opening AUTOEXEC.BAT\n");
	     else
	       {
		 segread (&segs);

		 while (fgets (data_buffer, sizeof(data_buffer), data))
		   {
		     // Copy data_buffer to extended memory 
		     string_length = strlen(data_buffer);

		     block.byte_count = string_length + 1; 

		     // transfer amount must be even
		     if (block.byte_count % 2)
		       block.byte_count++;

		     block.source_handle = 0; 
		     block.source_offset = (void far *)
			 MK_FP(segs.ds, data_buffer);
		     block.destination_handle = handle;
		     block.destination_offset = character_count;
		     character_count += string_length + 1;

		     inregs.h.ah = 0xB;
		     inregs.x.si = (unsigned) &block;

		     xms_access (&inregs, &outregs);

		     if (outregs.x.ax == 0)
		       {
			  transfer_error = 1;
			  break;
		       }                                                           
		   }
	       }

	     if (transfer_error)
	       printf ("Error in data transfer\n");
	     else
	       {
		  block.destination_handle = 0;
		  block.source_handle = handle;
		  block.destination_offset = (void far *)
		    MK_FP(segs.ds, data_buffer);
		     
		  block.source_offset = 0L;
		  block.byte_count = sizeof(data_buffer);

		  while (block.source_offset <
		     character_count)
		   {    
		     if ((block.byte_count + block.source_offset) 
			> character_count)
		       block.byte_count = character_count - 
			 block.source_offset;

		     // Transfer amount must be even
		     if (block.byte_count % 2)
		       {
			 block.byte_count++;
			 extra_byte = 1;
		       }
		     else 
		       extra_byte = 0;

		     xms_access (&inregs, &outregs);                  
				
		     if (outregs.x.ax == 0)
		       {
			 transfer_error = 1;
			 break; 
		       } 
		      
		     for (i = 0; i < (block.byte_count - 
			  extra_byte); i++)
		       if (data_buffer[i])
			 putchar(data_buffer[i]);
 
		     block.source_offset += block.byte_count;
		  }                        
	       } 

	     if (transfer_error)
	       printf ("Error in data transfer\n");  

	     // Release extended memory 
	     inregs.h.ah = 0x0A;
	     inregs.x.dx = handle;

	     xms_access (&inregs, &outregs);

	     if (outregs.x.ax == 0)
	       printf ("Error releasing extending memory %2xH\n", 
		 outregs.h.bl);
	   }  
      }
  }  
