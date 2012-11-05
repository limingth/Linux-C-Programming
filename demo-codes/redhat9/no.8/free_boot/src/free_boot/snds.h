/*************************************************************************/
/* Format of the Program Status Register                                 */
/*************************************************************************/
/*                                                                       */
/* 31  30  29   28         7   6   5   4   3   2   1   0                 */
/*+---+---+---+---+--ss--+---+---+---+---+---+---+---+---+               */
/*| N | Z | C | V |      | I | F | T |     M4 ~ M0       |               */
/*+---+---+---+---+--ss--+---+---+---+---+---+---+---+---+               */
/*                                                                       */
/* Processor Mode and Mask                                               */
/*                                                                       */
/*************************************************************************/

#ifndef	SNDS_H	
#define	SNDS_H 

#define Mode_USR        0x10	@ 00010000
#define Mode_FIQ        0x11	@ 00010001
#define Mode_IRQ        0x12	@ 00010010
#define Mode_SVC        0x13 	@ 00010011
#define Mode_ABT        0x17	@ 00010111
#define Mode_UND        0x1B	@ 00011011
#define Mode_SYS        0x1F 	@ 00011111
#define MASK_MODE		0x0000003F	@ 00111111
#define MODE_SVC32		0x00000013	@ 00010011

#define I_BIT           0x80 @ when I bit is set, IRQ is disabled 0x10000000
#define F_BIT           0x40 @ when F bit is set, FIQ is disabled 0x01000000


#define ASIC_BASE  	 	0x03ff0000

/*SYSTEM MANAGER REGISTERS*/

#define ARM7_SYSCFG	    (ASIC_BASE+0x0000)
#define ARM7_CLKCON  	(ASIC_BASE+0x3000)
#define ARM7_EXTACON0   (ASIC_BASE+0x3008)
#define ARM7_EXTACON1   (ASIC_BASE+0x300c)
#define ARM7_EXTDBWTH   (ASIC_BASE+0x3010)
#define ARM7_ROMCON0  	(ASIC_BASE+0x3014)
#define ARM7_ROMCON1  	(ASIC_BASE+0x3018)
#define ARM7_ROMCON2  	(ASIC_BASE+0x301c)
#define ARM7_ROMCON3  	(ASIC_BASE+0x3020)
#define ARM7_ROMCON4  	(ASIC_BASE+0x3024)
#define ARM7_ROMCON5  	(ASIC_BASE+0x3028)
#define ARM7_DRAMCON0   (ASIC_BASE+0x302c)
#define ARM7_DRAMCON1   (ASIC_BASE+0x3030)
#define ARM7_DRAMCON2   (ASIC_BASE+0x3034)
#define ARM7_DRAMCON3   (ASIC_BASE+0x3038)
#define ARM7_REFEXTCON  (ASIC_BASE+0x303c)


/*controller registers*/

#define ARM7_INTMODE 	(ASIC_BASE+0x4000)
#define ARM7_INTPEND 	(ASIC_BASE+0x4004)
#define ARM7_INTMASK 	(ASIC_BASE+0x4008)
#define ARM7_INTOFFSET  (ASIC_BASE+0x4024)
#define ARM7_INTPENDTST (ASIC_BASE+0x402c)
#define ARM7_INTPRI0 	(ASIC_BASE+0x400C)
#define ARM7_INTPRI1 	(ASIC_BASE+0x4010)
#define ARM7_INTPRI2 	(ASIC_BASE+0x4014)
#define ARM7_INTPRI3 	(ASIC_BASE+0x4018)
#define ARM7_INTPRI4 	(ASIC_BASE+0x401C)
#define ARM7_INTPRI5 	(ASIC_BASE+0x4020)
#define ARM7_INTOSET_FIQ  	(ASIC_BASE+0x4030)
#define ARM7_INTOSET_IRQ  	(ASIC_BASE+0x4034)


/* I/O Port Interface */

#define ARM7_IOPMOD 		(ASIC_BASE+0x5000)
#define ARM7_IOPCON 	 	(ASIC_BASE+0x5004)
#define ARM7_IOPDATA 		(ASIC_BASE+0x5008)

/* IIC Registers */
#define ARM7_IICCON    		(ASIC_BASE+0xf000)
#define ARM7_IICBUF    		(ASIC_BASE+0xf004)
#define ARM7_IICPS     		(ASIC_BASE+0xf008)
#define ARM7_IICCNT    		(ASIC_BASE+0xf00c)

/* UART Port Registers */
#define ARM7_UART_0			(ASIC_BASE+0xd00c)



/*************************************************************************/
/*  SYSTEM MEMORY CONTROL REGISTER EQU TABLES                            */
/*************************************************************************/



/***************Init***************/
#define rEXTDBWTH		0x00003001
#define rROMCON0		0x02000060
#define rROMCON1  		0x60
#define rROMCON2   		0x60
#define rROMCON3   		0x60
#define rROMCON4   		0x60
#define rROMCON5   		0x60
#define rSDRAMCON0   	0x12008380
#define rSDRAMCON1   	0x00
#define rSDRAMCON2   	0x00
#define rSDRAMCON3   	0x00
#define rSREFEXTCON		0xCE278360



/************Memory Remap**************/
#define rEXTDBWTH_R		0x00003001
#define rROMCON0_R		0x12040060
#define rROMCON1_R  	0x60
#define rROMCON2_R   	0x60
#define rROMCON3_R   	0x60 
#define rROMCON4_R   	0x60
#define rROMCON5_R   	0x60
#define rSDRAMCON0_R   	0x10000380
#define rSDRAMCON1_R   	0x00
#define rSDRAMCON2_R   	0x00
#define rSDRAMCON3_R   	0x00
#define rSREFEXTCON_R	0xCE278360

#endif


