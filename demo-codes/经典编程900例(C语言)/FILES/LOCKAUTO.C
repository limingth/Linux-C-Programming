#include <stdio.h>
#include <io.h>
#include <share.h>
#include <fcntl.h>

void main(void)
 {
   int handle;

   if ((handle = sopen("\\AUTOEXEC.BAT", O_RDONLY, SH_DENYNO)) == -1)
     printf("Error opening AUTOEXEC.BAT\n");
   else
    {
      lock(handle, 0L, 5L);
      printf("File locked--press Enter to continue\n");
      getchar();
      close(handle);
    }
 }

