#include <stdio.h>

void main(void)
 {
   enum { Monday, Tuesday, Wednesday, Thursday, Friday } day;

   
   for (day = Monday; day <= Friday; day++)
    if (day == Monday)
      printf("No fun---meetings all day Monday\n");
    else if (day == Tuesday)
      printf("No fun---do Monday's work today\n");
    else if (day == Wednesday)
      printf("Hump day...");
    else if (day == Thursday)
      printf("Schedule meetings for next Monday\n");
    else 
      printf("Meet everyone at happy hour!\n");
 }   
