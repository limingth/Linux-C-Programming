#include <stdio.h>

void main(int argc, char *argv[])
 {
   while (*++argv)
     if (remove(*argv))
       printf("Error removing %s\n", *argv);
 }
