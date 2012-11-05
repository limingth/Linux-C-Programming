#include <stdio.h>
#include <dos.h>
#include <stdlib.h>

void main (void)
  {
    struct fcbs {
      char drive; 
      char filename[8]; 
      char extension[3];
      int current_block;
      int record_size;
    };

    typedef struct fcbs fcb;

    struct program_segment_prefix {
      char near *int20;
      char near *next_paragraph_segment;
      char reserved_1;
      char dos_dispatcher[5];
      char far *terminate_vector;
      char far *ctrlc_vector;
      char far *critical_error_vector;
      char near *parent_psp; 
      unsigned char file_table[20];
      char near *environment_block_segment;
      char far *stack_storage;
      int  handles_available;
      char far *file_table_address;
      char far *shares_previous_psp;
      char reserved_2[20];
      char dos_int21_retf[3];
      char reserved_3[9];
      fcb fcb1;
      fcb fcb2;
      char reserved_4[4];
      char command_tail[128];
    } far *psp;

    int i;

    psp = (struct program_segment_prefix far *) ((long) _psp << 16);
 
    for (i = 0; i < 20; i++)
      printf("Entry %d contains %x\n", i, psp->file_table[i]);
  }
