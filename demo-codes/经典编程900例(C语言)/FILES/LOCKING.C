#include <stdio.h>
#include <io.h>
#include <share.h>
#include <fcntl.h>
#include <sys\locking.h>

void main(void)
 {
   int handle;

   if ((handle = sopen("\\AUTOEXEC.BAT", O_RDONLY, SH_DENYNO)) == -1)
     printf("Error opening AUTOEXEC.BAT\n");
   else
    {
      printf("Trying to lock file\n");
      if (locking(handle, LK_LOCK, 5L))
         printf("Error locking file\n");
      else
       {
         printf("File locked--press Enter to continue\n");
         getchar();
         close(handle);
       }
    }
 }

