#include <stdio.h>
#include <fcntl.h>  // Contains the _fmode declaration

void main(void)
 {
   if (_fmode == O_TEXT)
     printf("Text mode translations\n");
   else
     printf("Binary mode translations\n");
 }



