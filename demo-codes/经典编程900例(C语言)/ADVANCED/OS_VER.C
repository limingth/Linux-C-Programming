#include <stdio.h>
#include <dos.h>

void main (void)
 {
   printf("Operating system version number %d.%d\n",
    _osmajor, _osminor);
   
   printf("Operating system version number %d.%d\n",
    _version & 255, _version >> 8);
 }

