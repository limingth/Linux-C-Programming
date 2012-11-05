int fstreql(char far *str1, char far *str2)
 {
   while ((*str1 == *str2) && (*str1))
     {
       str1++;
       str2++;
     }

   return((*str1 == NULL) && (*str2 == NULL));
 }
