#include <stdio.h>
#include <string.h>

void main(void)
 {
   printf("Looking for Abc in AbcDef %s\n",
    (strstr("AbcDef", "Abc")) ? "Found" : "Not found");
   printf("Looking for Abc in abcDef %s\n",
    (strstr("abcDef", "Abc")) ? "Found" : "Not found");
   printf("Looking for Abc in AbcAbc %s\n",
    (strstr("AbcAbc", "Abc")) ? "Found" : "Not found");
 }

