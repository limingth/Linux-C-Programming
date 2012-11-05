#include <stdio.h>
#include <stdlib.h>
#include <dir.h>
#include <errno.h>

void main (int argc, char *argv[])
  {
    char directory[MAXPATH];

    if (argc == 1)  // Display the current directory
      {
        getcwd(directory, MAXPATH);
        puts(directory);
      }
    else if ((chdir(argv[1])) && (errno == ENOENT))
      puts("Invalid directory");
  }
          

