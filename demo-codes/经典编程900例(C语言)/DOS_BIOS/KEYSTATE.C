#include <stdio.h>
#include <bios.h>

void main(void)
 {
   unsigned int state, old_state = 0;

   do {
     state = _bios_keybrd(_KEYBRD_SHIFTSTATUS);

     if (state != old_state)
       {
         old_state = state;

         if (state & 0x80)
           printf("Ins On ");
         if (state & 0x40)
           printf("Caps On ");
         if (state & 0x20)
           printf("Num Lock On ");
         if (state & 0x10)
           printf("Scroll Lock On ");
         if (state & 0x08)
           printf("Alt pressed ");
         if (state & 0x04)
           printf("Ctrl pressed ");
         if (state & 0x02)
           printf("Left shift pressed ");
         if (state & 0x01)
           printf("Right shift pressed ");
         printf("\n");
      }
   } while (! _bios_keybrd(_KEYBRD_READY));
 }

