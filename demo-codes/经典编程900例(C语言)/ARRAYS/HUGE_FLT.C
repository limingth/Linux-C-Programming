#include <stdio.h>
#include <malloc.h>

void main (void)
  {
     int i;

     float huge *values;

     if ((values = (float huge *) halloc (17000,
	sizeof(float))) == NULL)
       printf ("Error allocating huge array\n");
     else
       {             
	 printf("Filling the array\n");

	 for (i = 0; i < 17000; i++)
	   values[i] = i * 1.0;

	 for (i = 0; i < 17000; i++)
	   printf ("%8.1f ", values[i]);

	 hfree(values);
       }
  }
