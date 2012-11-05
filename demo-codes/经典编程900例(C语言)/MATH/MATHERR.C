#include <stdio.h>
#include <math.h>

void main(void)
 {
   printf("Sqrt of -1 is %f\n", sqrt(-1.0));
 }

int matherr(struct exception *error)
 {
   switch (error->type) {
     case DOMAIN: printf("Domain error\n");
                  break;
     case PLOSS:  printf("Partial precision loss error\n");
                  break; 
     case OVERFLOW: printf("Overflow error\n");
                    break;
     case SING:   printf("Error in singularity\n");
                  break;
     case TLOSS:  printf("Total precision loss error\n");
                  break;
     case UNDERFLOW: printf("Underflow error\n");
                     break;
   };
   printf("Error occurred in %s values %f\n",
     error->name, error->arg1);
   error->retval = 1;
   return(1);
  }


    
