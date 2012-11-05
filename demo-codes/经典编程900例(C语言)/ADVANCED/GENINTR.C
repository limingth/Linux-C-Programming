#include <stdio.h>
#include <dos.h>
#include <stdlib.h>

void interrupt far (*original_handler)();

void interrupt far handler(void)
 {
   printf("Some event just happened\n");
   _disable();
   _dos_setvect(0xFF, original_handler);
   _enable();
   
   exit(0);
 }

void main(void)
 { 
  int i = 0;

  
  original_handler = _dos_getvect(0xFF);

  _disable();
  _dos_setvect(0xFF, handler);
  _enable();

  while (i++ < 100) 
    ;
  geninterrupt(0xFF);
 }

