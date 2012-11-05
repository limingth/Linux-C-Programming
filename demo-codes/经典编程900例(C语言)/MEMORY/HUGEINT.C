#include <stdio.h>
#include <malloc.h>

void main (void)
  {
     long int i;

     int huge *big_array;

     if ((big_array = (int huge *) halloc (100000L,
	sizeof(long int))) == NULL)
       printf ("Error allocating huge array\n");
     else
       {             
	 printf("Filling the array\n");

	 for (i = 0; i < 100000L; i++)
	   big_array[i] = i % 32768;

	 for (i = 0; i < 100000L; i++)
	   printf ("%d ", big_array[i]);

	 hfree(big_array);
       }
  }
