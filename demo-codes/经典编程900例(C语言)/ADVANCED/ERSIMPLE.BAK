#include <stdio.h>
#include <dos.h>
#include <conio.h>

void far handler(unsigned device_error, unsigned error_code,
  unsigned far *device_header)
 {
   cputs("Critical error ending program\n");
   _hardresume(_HARDERR_ABORT);   // Abort
 }

void main(void)
 {
   FILE *fp;

   _harderr(handler);

   fp = fopen("A:SOMEFILE.EXT", "r");

   printf("Program message...\n");
   fclose(fp);
 }

   
