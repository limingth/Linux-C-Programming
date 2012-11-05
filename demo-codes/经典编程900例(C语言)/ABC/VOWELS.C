#include <stdio.h>

void main()
 {
   char letter;

   int vowel_count = 0;
   
   for (letter = 'A'; letter <= 'Z'; letter++)
     switch (letter) {
       case 'A':
       case 'E':
       case 'I':
       case 'O':
       case 'U': vowel_count++;
     }; 
 
   printf("The number of vowels is %d\n", vowel_count);
 }
