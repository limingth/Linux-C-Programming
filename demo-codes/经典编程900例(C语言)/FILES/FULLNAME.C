#include <stdio.h>
#include <stdlib.h>

void main (void) 
 {
   char *file = "FILENAME.EXT";

   char *full_name = NULL;

   if (full_name = _fullpath(NULL, file, _MAX_PATH))
     {
       printf ("Full name for %s is %s\n", file, full_name);
       free (full_name);
     }
   else 
     {
       printf("Unable to allocate memory for the full name\n");
       exit (1);
     }
  }


