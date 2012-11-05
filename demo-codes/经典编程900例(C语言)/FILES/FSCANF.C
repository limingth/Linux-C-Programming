#include <stdio.h>

void main(void)
 {
   FILE *fp;

   int age;
   float salary;
   char name[64];

   if ((fp = fopen("DATA.DAT", "w")) == NULL)
     printf("Error opening DATA.DAT for output\n");
   else
     {
       fprintf(fp, "33 35000.0 Kris");
       fclose(fp);
   
       if ((fp = fopen("DATA.DAT", "r")) == NULL)
         printf("Error opening DATA.DAT for input\n");
       else
        {
          fscanf(fp, "%d %f %s", &age, &salary, name);
          printf("Age %d Salary %f Name %s\n", age, salary, name);
          fclose(fp);
        }
     }
 }
