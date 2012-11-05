#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <sys\stat.h>

void main(void)
 {
   int handle;
   int duplicate_handle;

   char title[] = "Jamsa's 1001 C/C++ Tips!";
   char section[] = "Files";

   if ((handle = open("OUTPUT.TST", O_WRONLY | O_CREAT, 
        S_IWRITE)) == -1)
     printf("Error opening OUTPUT.TST\n");
   else
    {
      if ((duplicate_handle = dup(handle)) == -1)
        printf("Error duplicating handle\n");
      else
        {
          write(handle, title, sizeof(title));
          close(duplicate_handle);  // Flush the buffer
          write(handle, section, sizeof(section));
          close(handle);
        }
    }
 }

