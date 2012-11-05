#include <stdio.h>
#include <process.h>

void main(void)
 {
   char *env[] = { "FILENAME=SPAWNVXX.C", "OS=DOS", 
                   "ROUTINE=EXECVPE", NULL };

   char *argv[] = { "CHILD.EXE", "AAA", "BBB", NULL };

   execvpe("CHILD.EXE", argv, env);
 }

