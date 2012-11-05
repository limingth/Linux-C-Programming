#include <stdio.h>
#include <dos.h>

void main (void)
 {
   struct date curr_date;
   struct time curr_time;

   FILE *output;

   getdate(&curr_date);
   gettime(&curr_time);

   if ((output = fopen("DATETIME.OUT", "w")) == NULL)
     fprintf(stderr, "Error opening file DATETIME.OUT\n");
   else
     {
       fwrite(&curr_date, sizeof(curr_date), 1, output);
       fwrite(&curr_time, sizeof(curr_time), 1, output);
       fclose(output);
     }
 }
