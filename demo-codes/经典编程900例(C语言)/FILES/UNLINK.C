#include <stdio.h>

void main(int argc, char *argv[])
 {
   while (*++argv)
     if (unlink(*argv))
       printf("Error removing %s\n", *argv);
 }
