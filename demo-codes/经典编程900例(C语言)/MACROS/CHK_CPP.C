#include <stdio.h>

void main ()
 {
#ifdef __cplusplus
  printf("Using C++\n");
#else
  printf("Using C\n");
#endif
 }
