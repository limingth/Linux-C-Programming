#include <stdio.h>
#include <stdlib.h>

void main (void)
 {
   char pathname[_MAX_PATH];

   char *drive = "C:";
   char *subdir = "\\SUBDIR";
   char *filename = "FILENAME";
   char *extension = "EXT";

   _makepath(pathname, drive, subdir, filename, extension);

   printf("The complete pathname is %s\n", pathname);
 }

