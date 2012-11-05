#include <stdio.h>

void unknown_title(void)
 {
   printf("The book's title is %s\n", title);
 }

char title[] = "Jamsa's 1001 C/C++ Tips";

void main(void)
 {
   printf("Title: %s\n", title);
 }

