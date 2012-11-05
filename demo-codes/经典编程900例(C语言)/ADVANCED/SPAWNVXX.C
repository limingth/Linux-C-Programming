#include <stdio.h>
#include <process.h>

void main(void)
 {
   char *env[] = { "FILENAME=SPAWNVXX.C", "OS=DOS", 
                   "ROUTINES=SPAWNVXX", NULL };

   char *argv[] = { "CHILD.EXE", "AAA", "BBB", NULL };

   spawnv(P_WAIT, "CHILD.EXE", argv);
   spawnve(P_WAIT, "CHILD.EXE", argv, env);
   spawnvp(P_WAIT, "CHILD.EXE", argv);
   spawnvpe(P_WAIT, "CHILD.EXE", argv, env);
 }

