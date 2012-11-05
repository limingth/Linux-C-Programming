#include <conio.h>

void main(void)
 {
   union TextColor {
     struct {
      unsigned char foreground:4;
      unsigned char background:3;
      unsigned char blinking:1;
     } color_bits;
     unsigned char value;
   } colors;
   colors.color_bits.foreground = BLUE;
   colors.color_bits.background = RED;
   colors.color_bits.blinking = 1;

   textattr(colors.value);

   clrscr();
   cprintf("This is the new text colors\n");
 }

