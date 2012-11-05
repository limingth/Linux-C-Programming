#include <stdio.h>
#include <dirent.h>
#include <alloc.h>
#include <string.h>
#include <stdlib.h>

void main(int argc, char *argv[])
 { 
   DIR *directory_pointer;
   struct dirent *entry;

   struct FileList {
     char filename[64];
     struct FileList *next;
   } start, *node;
   
   
   if ((directory_pointer = opendir(argv[1])) == NULL)
     printf("Error opening %s\n", argv[1]);
   else
     {
        start.next = NULL;
        node = &start;

        while (entry = readdir(directory_pointer))
          { 
            node->next = (struct FileList *) malloc(sizeof(struct FileList));           
            if (node == NULL)
             {
               printf("Insufficient memory to store list\n");
               exit(1);
             }
            node = node->next;
            strcpy(node->filename, entry);
            node->next = NULL;
          }

        closedir(directory_pointer);
     
     
        node = start.next;

        while (node)
          {
            printf("%s\n", node->filename);
            node = node->next;
          }

     }
 }


