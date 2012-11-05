#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>

void main(void)
 {
   char buffer[8000];
   int handle;

   if ((handle = creat("SAVESCR.DAT", S_IWRITE)) == -1) 
    cprintf("Error opening SAVESCRN.DAT\r\n");
   else
     {
       gettext(1, 1, 80, 25, buffer);
       write(handle, buffer, sizeof(buffer));
       close(handle);
     }
 }

