#include <stdio.h>
#include <string.h>

void main(void)
 {
   printf("Searching for Abc in AbcDef %d\n",
     strspn("AbcDef", "Abc"));
   
   printf("Searching for cbA in AbcDef %d\n",
     strspn("AbcDef", "cbA"));
   
   printf("Searching for Def in AbcAbc %d\n",
     strspn("AbcAbc", "Def"));
 }


