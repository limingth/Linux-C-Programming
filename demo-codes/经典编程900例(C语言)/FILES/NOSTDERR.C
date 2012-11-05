#include <stdio.h>

void main(void)
 {
   if (freopen("STANDARD.ERR", "w", stderr))
     fputs("stderr has been redirected", stderr);
   else
     printf("Error in reopen\n");
 }

