#include <stdio.h>
#include <dirent.h>

void main(int argc, char *argv[])
 { 
   DIR *directory_pointer;
   struct dirent *entry;

   if ((directory_pointer = opendir(argv[1])) == NULL)
     printf("Error opening %s\n", argv[1]);
   else
     {
        while (entry = readdir(directory_pointer))
          printf("%s\n", entry);
        closedir(directory_pointer);
     }
 }


