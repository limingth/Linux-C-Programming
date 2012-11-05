#include <stdio.h>

void main ()
 {
   char *near_title = "Jamsa's 1001 C & C++ Tips";
   char far *far_title = "Jamsa's 1001 C & C++ Tips";

   printf("The book's title: %Ns\n", near_title);
   printf("The book's title: %Fs\n", far_title);
 }
