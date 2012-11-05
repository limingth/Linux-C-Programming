/*-------------------------------------------------------------------------
 * Filename:      ld-script
 * Version:       $Id: start-ld-script,v 1.1 2001/10/07 15:51:01 erikm Exp $
 * Copyright:     Copyright (C) 1999, Erik Mouw
 * Author:        Erik Mouw <J.A.K.Mouw@its.tudelft.nl>
 * Description:   ld (linker) script to make the blob bootlader.
 *                Heavily inspired by the Linux kernel linker scripts.
 * Created at:    Tue Aug 24 17:24:06 1999
 * Modified by:   Erik Mouw <J.A.K.Mouw@its.tudelft.nl>
 * Modified at:   Sun Aug 29 14:45:54 1999
 *-----------------------------------------------------------------------*/
/* OUTPUT_FORMAT("elf32-arm", "elf32-arm", "elf32-arm") */
/* OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm") */

OUTPUT_ARCH(arm)
ENTRY(__text_start)
SECTIONS
{
	.text 0x00000 : {		
		__text_start = .;	
		init.o (.text)
		*.o (.text)
		*.o (.rodata)
		. = ALIGN(4);
		__text_end = .;		
	}

	.data : {
		__data_start = .;
		*(.data)
		. = ALIGN(4);
		__data_end = .;
	}

	.bss : {
		__bss_start = .;	
		*(.bss)
		. = ALIGN(4);
		__bss_end = .;
	}

}

