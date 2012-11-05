#include <stdio.h>

void main(void)
 {
   FILE *input;

   if ((input = fopen("\\CONFIG.SYS", "r")) == NULL)
     printf("Error opening \\CONFIG.SYS\n");
   else
     {
       printf("Handle for CONFIG.SYS %d\n", input->fd);
       printf("Handle for stdin %d\n", stdin->fd);
       printf("Handle for stdout %d\n", stdout->fd);
       printf("Handle for stderr %d\n", stderr->fd);
       printf("Handle for stdaux %d\n", stdaux->fd);
       printf("Handle for stdprn %d\n", stdprn->fd);

       fclose(input);
     }
  }

