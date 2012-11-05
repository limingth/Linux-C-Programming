#include <stdio.h>
#include <dir.h>

void main(void)
 {
   char name_a[13] = "ACCTNGXXXXXX";
   char name_b[13] = "COMPUTXXXXXX";
   char name_c[13] = "PCCHIPXXXXXX";

   if (mktemp(name_a))
     puts(name_a);
   
   if (mktemp(name_b))
     puts(name_b);
   
   if (mktemp(name_c))
     puts(name_c);
 }


