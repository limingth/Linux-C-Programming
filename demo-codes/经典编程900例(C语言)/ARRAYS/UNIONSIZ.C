#include <stdio.h>

void main(void)
 {
   union EmployeeDates {
     int days_worked;
     struct Date {
       int month;
       int day;
       int year;
     } last_day;
   } emp_info;

   union Numbers {
     int a;
     float b;
     long c;
     double d;  // Largest--requires 8 bytes
   } value;

   printf("Size of EmployeeDates %d bytes\n", sizeof(emp_info));
   printf("Size of Numbers %d bytes\n", sizeof(value));
 }

