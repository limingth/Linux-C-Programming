/*   
 *  skyeye_printf.c  
 *  this file implement printf function on AT91X40 in SkyEye 
 *  for Atmel AT91 output
 *
 *  Bugs report:     li ming  ( lmcs00@mails.tsinghua.edu.cn )
 *  Last modified:   2003-02-02 
 * 
 *  Thanks to wahaha@smth.org who provided the main source code 
 */
 
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

#include "skyeye-stdio.h"

#ifndef  TRUE
#define  TRUE 1
#endif
#ifndef  FALSE
#define  FALSE 0
#endif

static int do_padding;
static int left_flag;
static int len;
static int num1;
static int num2;
static char pad_character;

/*---------------------------------------------------*/
/*                                                   */
/* This routine puts pad characters into the output  */
/* buffer.                                           */
/*                                                   */
static void padding( const int l_flag)
{
   int i;
   if (do_padding && l_flag && (len < num1))
      for (i=len; i<num1; i++)
          skyeye_putc( pad_character);
}

/*---------------------------------------------------*/
/*                                                   */
/* This routine moves a string to the output buffer  */
/* as directed by the padding and positioning flags. */
/*                                                   */
static void outs( char* lp)
{
   /* pad on left if needed                          */
   len = strlen( lp);
   padding( !left_flag);
   /* Move string to the buffer                      */
   while (*lp && num2--)
      skyeye_putc( *lp++);
   /* Pad on right if needed                         */
   len = strlen( lp);
   padding( left_flag);
}
/*---------------------------------------------------*/
/*                                                   */
/* This routine moves a number to the output buffer  */
/* as directed by the padding and positioning flags. */
/*                                                   */
static void reoutnum(unsigned long num, unsigned int negative, const long base )
{
   char* cp;
   char outbuf[32];
   const char digits[] = "0123456789ABCDEF";

   /* Build number (backwards) in outbuf             */
   cp = outbuf;
   do {
      *cp++ = digits[(int)(num % base)];
      } while ((num /= base) > 0);
   if (negative)
      *cp++ = '-';
   *cp-- = 0;
   /* Move the converted number to the buffer and    */
   /* add in the padding where needed.               */
   len = strlen(outbuf);
   padding( !left_flag);
   while (cp >= outbuf)
      skyeye_putc( *cp-- );
   padding( left_flag);
}

static void outnum(long num, const long base ,unsigned char sign)//1, signed  0 unsigned
{   unsigned int negative;
   if ( (num < 0L) && sign )
   {  
	  negative=1;
      num = -num;
   }
   else negative=0;
   reoutnum(num,negative,base);
}
/*---------------------------------------------------*/
/*                                                   */
/* This routine gets a number from the format        */
/* string.                                           */
/*                                                   */
static int getnum( char** linep)
{
   int n;
   char* cp;
   n = 0;
   cp = *linep;
   while (isdigit(*cp))
      n = n*10 + ((*cp++) - '0');
   *linep = cp;
   return(n);
}
/*---------------------------------------------------*/
/*                                                   */
/* This routine operates just like a printf/sprintf  */
/* routine. It outputs a set of data under the       */
/* control of a formatting string. Not all of the    */
/* standard C format control are supported. The ones */
/* provided are primarily those needed for embedded  */
/* systems work. Primarily the floaing point         */
/* routines are omitted. Other formats could be      */
/* added easily by following the examples shown for  */
/* the supported formats.                            */
/*                                                   */

void skyeye_printf( char* ctrl, ...)
{
   int long_flag;
   int dot_flag;
   char ch;
   char lower;
   int ret;
   va_list argp;
   va_start( argp, ctrl);
   for ( ; *ctrl; ctrl++) {
      /* move format string chars to buffer until a  */
      /* format control is found.                    */
      if (*ctrl != '%') {
         skyeye_putc(*ctrl);
#if CR_as_CRLF==TRUE
         if(*ctrl=='\n') skyeye_putc('\r');
#endif
         continue;
         }
      /* initialize all the flags for this format.   */
      dot_flag   =
      long_flag  =
      left_flag  =
      do_padding = 0;
      pad_character = ' ';
      num2=32767;
try_next:
      ch = *(++ctrl);
      ret = isdigit(ch); 
      if (ret) {
         if (dot_flag)
            num2 = getnum(&ctrl);
         else {
            if (ch == '0')
               pad_character = '0';
            num1 = getnum(&ctrl);
            do_padding = 1;
         }
         ctrl--;
         goto try_next;
      }
      lower = tolower(ch);
      switch (ch) {
         case '%':
              skyeye_putc( '%');
              continue;
         case '-':
              left_flag = 1;
              break;
         case '.':
              dot_flag = 1;
              break;
         case 'l':
              long_flag = 1;
              break;
         case 'd':
              if (long_flag ==1 ) {
                if(ch == 'D')                {outnum( va_arg(argp, unsigned long), 10L , 0);continue;}
                       else  /* ch == 'd' */        {outnum( va_arg(argp, long), 10L,1);continue;}
                 }
              else {
                if(ch == 'D')                {outnum( va_arg(argp, unsigned int),10L,0);continue;}
                else  /* ch == 'd' */        {outnum( va_arg(argp, int), 10L,1);continue;}
                }
         case 'x':    // X ??? , x  ???
              if (long_flag ==1 )  {
                       if(ch == 'X')                {outnum( va_arg(argp, unsigned long), 16L,0);continue;}
                       else  /* ch == 'x' */        {outnum( va_arg(argp, long), 16L,1);continue;}
                 }
              else {
                if(ch == 'X')                {outnum( va_arg(argp, unsigned int), 16L,0);continue;}
                else  /* ch == 'x' */        {outnum( va_arg(argp, int), 16L,1);continue;}
                 } //????16????,???????????
              continue;
         case 's':
              outs( va_arg( argp, char*));
              continue;
         case 'c':
              skyeye_putc( (char) va_arg(argp, int) );
              continue;

         default:
              continue;
         }
      goto try_next;
      }
   va_end( argp);
}

