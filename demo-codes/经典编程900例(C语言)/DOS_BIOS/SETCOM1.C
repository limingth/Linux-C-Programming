#include <stdio.h>
#include <bios.h>

void main(void)
 {
   char i = 0, title[] = "Jamsa's 1001 C/C++ Tips";

   unsigned status;

   status = _bios_serialcom(_COM_INIT, 0, _COM_9600 | _COM_CHR8 | _COM_STOP1 |
        _COM_NOPARITY);

   if (status & 0x100) // Data ready
     while (title[i])
       {
         _bios_serialcom(_COM_SEND, 0, title[i]);
         putchar(title[i]);
         i++;
       }
 }

