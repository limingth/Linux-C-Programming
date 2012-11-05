/*
 *	main.c   - 	 the main file of the bootloader
 *	
 *	Author: 	yu feng <progeryf@gmail.com>
 *	Date:		2007-5-11
 *	Modify:		2007-5-28
 */

#include "snds.h"
#include "uart.h"
#include "led_api.h"
#include "my_printf.h"
#include "shell.h"
#include "command.h"

void load()
{
	int delay = 3000000;
	/*init the UART and set the baud rate*/ 
	uart_init(UART0_BASE, BAUD_19200);
	
	while(1)
	{
		/*set the led just for testing*/
		led_all_dark();
		led_one_light( 1 );
		led_delay( 1 );
		led_one_light( 3 );
		led_delay( 1 );
		
		my_printf("\r if you want use the shell please enter");
		while ( delay > 0)
		{
			if (RX_DATA(GET_STATUS(UART0_BASE)) != 0)
			{
				my_printf("\r       FREE BOOT \n");
				my_printf("\rif you want know how to use \n");
				my_printf("\rplease input help \n");
		
				/*enter the shell you can load and store the file*/
				shell_command();
			}
			delay--;
		}
		my_printf("\rbooting.......\n");

		/* if you does't press any in 10 seconds
	     * the uCliunx will be loader
		 */
		flashl(BIOS_BASE, DOWNLOAD_BIN_ADDR, BIOS_LOAD);
		
		/* this is a function pointer
		 * jump to the kernel
		 */
		((void (*)(void))(DOWNLOAD_BIN_ADDR)) ();
	}
}

