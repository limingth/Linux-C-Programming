#include <stdio.h>
#include <bios.h>

void main (void)
 {
   printf("BIOS Memory report %dKb\n", biosmemory());
   printf("BIOS Memory report %dKb\n", _bios_memsize());
 }
