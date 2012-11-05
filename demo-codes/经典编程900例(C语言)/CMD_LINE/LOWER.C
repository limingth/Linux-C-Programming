#include <stdio.h>
#include <ctype.h>  // Contains the tolower prototype

void main (void)
  {
    int letter;

    for (letter = getchar(); ! feof(stdin); letter = getchar())
      putchar(tolower(letter));
  }
