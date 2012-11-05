#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <time.h>

void main(void)
  {
    int handle;

    struct stat buffer;

    if ((handle = open("\\AUTOEXEC.BAT", O_RDONLY)) == -1)
     printf("Error opening \\AUTOEXEC.BAT\n");
    else
      {
        if (fstat(handle, &buffer))
          printf("Error getting file information\n");
        else
          printf("AUTOEXEC.BAT is %ld bytes Last used %s\n",
            buffer.st_size, ctime(&buffer.st_atime));
        close(handle);
      }
 }

           

