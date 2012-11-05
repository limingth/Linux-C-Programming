#include <stdio.h>
#include <dos.h>

void main(void)
 {
   struct fatinfo fat;

   getfatd(&fat);

   printf("Sectors per cluster %d\n", fat.fi_sclus);
   printf("Clusters per disk %u\n", fat.fi_nclus);
   printf("Bytes per cluster %d\n", fat.fi_bysec);
   printf("Disk type %x\n", fat.fi_fatid & 0xFF);
 }

