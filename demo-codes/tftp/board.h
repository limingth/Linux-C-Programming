/********************************************************/
/*							*/
/* Samsung S3C4510b					*/
/* Hayden Luo ym_luo@powermatic.com.sg			*/
/*							*/
/********************************************************/
#ifndef __S3C4510B_BOARD_H
#define __S3C4510B_BOARD_H

/*
 * define S3C4510b CPU master clock
 */
#define MHz		1000000
#define fMCLK_MHz	(50 * MHz)
#define fMCLK		(fMCLK_MHz / MHz)
#define MCLK2		(fMCLK_MHz / 2)

/*
 * ASIC Address Definition
 */
#define BASE_ADDR	0x3FF0000

/* ************************ */
/* System Manager Registers */
/* ************************ */
#define SYSCFG		(BASE_ADDR+0x0000)
#define CLKCON		(BASE_ADDR+0x3000)
#define EXTACON0	(BASE_ADDR+0x3008)
#define EXTACON1	(BASE_ADDR+0x300C)
#define EXTDBWTH	(BASE_ADDR+0x3010)
#define ROMCON0		(BASE_ADDR+0x3014)
#define ROMCON1		(BASE_ADDR+0x3018)
#define ROMCON2		(BASE_ADDR+0x301C)
#define ROMCON3		(BASE_ADDR+0x3020)
#define ROMCON4		(BASE_ADDR+0x3024)
#define ROMCON5		(BASE_ADDR+0x3028)
#define DRAMCON0	(BASE_ADDR+0x302C)
#define DRAMCON1	(BASE_ADDR+0x3030)
#define DRAMCON2	(BASE_ADDR+0x3034)
#define DRAMCON3	(BASE_ADDR+0x3038)
#define REFEXTCON	(BASE_ADDR+0x303C)

/* *********************** */
/* Ethernet BDMA Registers */
/* *********************** */
#define BDMATXCON	(BASE_ADDR+0x9000)
#define BDMARXCON	(BASE_ADDR+0x9004)
#define BDMATXPTR	(BASE_ADDR+0x9008)
#define BDMARXPTR	(BASE_ADDR+0x900C)
#define BDMARXLSZ	(BASE_ADDR+0x9010)
#define BDMASTAT	(BASE_ADDR+0x9014)
#define CAMBASE		(BASE_ADDR+0x9100)
/*
 * CAM		0x9100 ~ 0x917C
 * BDMATXBUF	0x9200 ~ 0x92FC
 * BDMARXBUF	0x9800 ~ 0x99FC
 */

/* ********************** */
/* Ethernet MAC Registers */
/* ********************** */
#define MACON		(BASE_ADDR+0xA000)
#define CAMCON		(BASE_ADDR+0xA004)
#define MACTXCON	(BASE_ADDR+0xA008)
#define MACTXSTAT	(BASE_ADDR+0xA00C)
#define MACRXCON	(BASE_ADDR+0xA010)
#define MACRXSTAT	(BASE_ADDR+0xA014)
#define STADATA		(BASE_ADDR+0xA018)
#define STACON		(BASE_ADDR+0xA01C)
#define CAMEN		(BASE_ADDR+0xA028)
#define EMISSCNT	(BASE_ADDR+0xA03C)
#define EPZCNT		(BASE_ADDR+0xA040)
#define ERMPZCNT	(BASE_ADDR+0xA044)
#define EXTSTAT		(BASE_ADDR+0x9040)

/* ************************ */
/* HDLC Channel A Registers */
/* ************************ */

/* ************************ */
/* HDLC Channel B Registers */
/* ************************ */

/* ******************* */
/* I/O Ports Registers */
/* ******************* */
#define IOPMOD		(BASE_ADDR+0x5000)
#define IOPCON		(BASE_ADDR+0x5004)
#define IOPDATA		(BASE_ADDR+0x5008)

/* ****************************** */
/* Interrupt Controller Registers */
/* ****************************** */
#define INTMOD		(BASE_ADDR+0x4000)
#define INTPND		(BASE_ADDR+0x4004)
#define INTMSK		(BASE_ADDR+0x4008)
#define INTPRI0		(BASE_ADDR+0x400C)
#define INTPRI1		(BASE_ADDR+0x4010)
#define INTPRI2		(BASE_ADDR+0x4014)
#define INTPRI3		(BASE_ADDR+0x4018)
#define INTPRI4		(BASE_ADDR+0x401C)
#define INTPRI5		(BASE_ADDR+0x4020)
#define INTOFFSET	(BASE_ADDR+0x4024)
#define INTPNDTST	(BASE_ADDR+0x402C)
#define INTOSET_FIQ	(BASE_ADDR+0x4030)
#define INTOSET_IRQ	(BASE_ADDR+0x4034)

#define INT_MODE_IRQ	0x000000
#define INT_MODE_FIQ	0x1FFFFF
#define INT_MASK_DIS	0x1FFFFF
#define INT_MASK_ENA	0x000000

/* ***************** */
/* I2C Bus Registers */
/* ***************** */

/* ************** */
/* GDMA Registers */
/* ************** */
// GDMA 0 Registers
#define GDMACON0        (BASE_ADDR+0xb000)
#define GDMASRC0        (BASE_ADDR+0xb004)
#define GDMADST0        (BASE_ADDR+0xb008)
#define GDMACNT0        (BASE_ADDR+0xb00c)

// GDMA 1 Registers
#define GDMACON1        (BASE_ADDR+0xc000)
#define GDMASRC1        (BASE_ADDR+0xc004)
#define GDMADST1        (BASE_ADDR+0xc008)
#define GDMACNT1        (BASE_ADDR+0xc00c)

/* ************** */
/* UART Registers */
/* ************** */
#define ULCON0		(BASE_ADDR+0xD000)
#define ULCON1		(BASE_ADDR+0xE000)
#define UCON0		(BASE_ADDR+0xD004)
#define UCON1		(BASE_ADDR+0xE004)
#define USTAT0		(BASE_ADDR+0xD008)
#define USTAT1		(BASE_ADDR+0xE008)
#define UTXBUF0		(BASE_ADDR+0xD00C)
#define UTXBUF1		(BASE_ADDR+0xE00C)
#define URXBUF0		(BASE_ADDR+0xD010)
#define URXBUF1		(BASE_ADDR+0xE010)
#define UBRDIV0		(BASE_ADDR+0xD014)
#define UBRDIV1		(BASE_ADDR+0xE014)

/* **************** */
/* Timers Registers */
/* **************** */
#define TMOD		(BASE_ADDR+0x6000)
#define TDATA0		(BASE_ADDR+0x6004)
#define TDATA1		(BASE_ADDR+0x6008)
#define TCNT0		(BASE_ADDR+0x600C)
#define TCNT1		(BASE_ADDR+0x6010)

/* **************** */
/* Interrupt        */
/* **************** */

#define INT_EXTINT0	0
#define INT_EXTINT1	1
#define INT_EXTINT2	2
#define INT_EXTINT3	3
#define INT_UARTTX0	4
#define INT_UARTRX0	5
#define INT_UARTTX1	6
#define INT_UARTRX1	7
#define INT_GDMA0	8
#define INT_GDMA1	9
#define INT_TIMER0	10
#define INT_TIMER1	11
#define INT_HDLCTXA	12
#define INT_HDLCRXA	13
#define INT_HDLCTXB	14
#define INT_HDLCRXB	15
#define INT_BDMATX	16
#define INT_BDMARX	17
#define INT_MACTX	18
#define INT_MACRX	19
#define INT_IIC		20
#define INT_GLOBAL	21


#define PSR_MODE_MASK   0x1f
#define PSR_USER_MODE   0x10
#define PSR_SVC_MODE    0x13
#define PSR_IRQ_MODE    0x12
#define PSR_FIQ_MODE    0x11
#define PSR_UNDEF_MODE  0x1b
#define PSR_ABORT_MODE  0x17

#define TAG_BASE	0x11000000

#define NOCACHE_BIT     0x04000000


#define VPint	*(volatile unsigned int *)
#define VPshort	*(volatile unsigned short *)
#define VPchar	*(volatile unsigned char *)

#define CAM_Reg(x)		(VPint(CAMBASE+((x)*0x4)))

#define inl(addr)        (VPint(addr))
#define outl(data, addr) (VPint(addr) = (data))

#endif  /* __S3C4510B_BOARD_H */
