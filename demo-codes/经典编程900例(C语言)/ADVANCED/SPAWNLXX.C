#include <process.h>
#include <stdio.h>

void main(void)
 {
   char *env[] = { "FILE=SPAWNLXX.C", "LANGUAGE=C",
                   "OS=DOS", NULL};

   spawnle(P_WAIT, "CHILD.EXE", "CHILD.EXE", 
      "Using-spawnle", "BBB", NULL, env);

   spawnlp(P_WAIT, "CHILD.EXE", "CHILD.EXE", "Using-spawnlp", 
      "BBB", NULL);
   spawnlpe(P_WAIT, "CHILD.EXE", "CHILD.EXE", "Using-spawnlpe", 
      "BBB", NULL, env);
 }

