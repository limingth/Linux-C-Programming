#include <stdio.h>

void main (int argc, char *argv[])
  {
    FILE *fp;        // File pointer

    char line[255];  // Line from file

    if ((fp = fopen(argv[1], "r")) == NULL)
      printf("Error opening %s\n", argv[1]);
    else
      {
        // Read and display each line of the file
        while (fgets(line, sizeof(line), fp))
          fputs(line, stdout);
        fclose (fp);   // Close the file
      }
  }
