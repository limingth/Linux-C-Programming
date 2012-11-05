int chrcnt(const char *string, int letter)
 {
   int count = 0;

   while (*string)
     if (*string == letter) 
       count++;

   return(count);
 }
