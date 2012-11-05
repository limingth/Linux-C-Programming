#include <stdio.h>
#include <sys\stat.h>
#include <io.h>

void main(int argc, char *argv[])
 {
   if (chmod(argv[1], S_IREAD))
     printf("Error setting %s\n", argv[1]);
 }

