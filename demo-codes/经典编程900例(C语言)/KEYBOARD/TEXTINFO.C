#include <conio.h>

void main(void)
 {
   struct text_info text;

   gettextinfo(&text);

   cprintf("Screen coordinates %d,%d to %d,%d\r\n",
     text.wintop, text.winleft, text.winbottom, text.winright);

   cprintf("Text attribute %d Normal attribute %d\r\n",
     text.attribute, text.normattr);

   cprintf("Screen height %d width %d\r\n", text.screenheight,
     text.screenwidth);

   cprintf("Cursor position was row %d column %d\r\n",
     text.cury, text.curx);
 }

