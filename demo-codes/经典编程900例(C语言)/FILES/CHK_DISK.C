#include <stdio.h>
#include <dos.h>
#include <malloc.h>

void main(void)
 {
   struct fatinfo fat;
   long sector, total_sectors;
   void *buffer;

   getfat(3, &fat);
   total_sectors = fat.fi_nclus * fat.fi_sclus;

   if ((buffer = malloc(fat.fi_bysec)) == NULL)
     printf("Error allocating sector buffer\n");
   else
     for (sector = 0; sector < total_sectors; sector++)
       if (absread(2, 1, sector, buffer) == -1) 
        { 
          printf("\n\007Error reading sector %ld press Enter\n", 
            sector);
          getchar();
        }
       else
         printf("Reading sector %ld\r", sector);
 }

