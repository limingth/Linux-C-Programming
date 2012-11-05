#include <stdio.h>

void main (int argc, char **argv)
  {
    while (*argv)
      printf ("%s\n", *argv++);
  }

