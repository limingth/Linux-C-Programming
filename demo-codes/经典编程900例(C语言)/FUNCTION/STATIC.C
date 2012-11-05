#include <stdio.h>

void print_reportcard(int printer_number)
 {
   static int student_id = 100;

   printf("Printing report card for student %d\n", student_id);
   student_id++;

   // Other statements here
 }

 void main(void)
  {
    print_reportcard(1);
    print_reportcard(1);
    print_reportcard(1);
  }
