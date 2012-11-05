#include <stdio.h>

void main(void)
 {
   char *workdays[] = {"Monday", "Tuesday", "Wednesday",
                        "Thursday", "Friday", "" };
   char **work_day;

   work_day = workdays; 

   while (*work_day)
     printf("%s\n", *work_day++);
 }

