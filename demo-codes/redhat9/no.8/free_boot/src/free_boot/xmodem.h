#ifndef _XMODEM_H
#define _XMODEM_H
//#include "priv_data.h"

/* XMODEM parameters */
#define BLOCK_SIZE	128	/* size of transmit blocks */
#define RETRIES		20	/* maximum number of RETRIES */

/* Line control codes */
#define SOH		0x01	/* start of header */
#define ACK		0x06	/* Acknowledge */
#define NAK		0x15	/* Negative acknowledge */
#define CAN		0x18	/* Cancel */
#define EOT		0x04	/* end of text */

#define GET_BYTE_TIMEOUT 10000000
#include "DataType.h"


#if 0
void bufputs(char *s);
void reset_debugbuf(void);
#endif

/*
 * receive data,and store it into memory dldaddr points 
 * if successful, return the real data's offset,else 
 * return 0
 */
U32 xmodem_receive(int argc, char* argv[]);

/*
 * Read a record in the XMODEM protocol, return the block number
 * (0-255) if successful, or one of the following return codes:
 * 	-1 = Bad byte
 * 	-2 = Bad block number
 * 	-3 = Bad block checksum
 * 	-4 = End of file
 * 	-5 = Canceled by remote
 */
int get_record(void);

#endif

