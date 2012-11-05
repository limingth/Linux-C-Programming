#include "types.h"
#include "bioscall.h"
#include "eth.h"
#include "board.h"
#include "utils.h"
#include "mac.h"

static struct frame_desc_struct rx_fd[RX_FRAME_SIZE];
static struct frame_desc_struct tx_fd[TX_FRAME_SIZE];

static struct frame_buf_struct rx_buf[RX_FRAME_SIZE];
static struct frame_buf_struct tx_buf[TX_FRAME_SIZE];

static unsigned long gtx_ptr;
static unsigned long grx_ptr;

static unsigned char s3c4510_eth_addr[ETH_ALEN] = {0x00,0x80,0x48,0x12,0x34,0x56};

//祯指针结构初始化,环形链表
static void s3c4510_eth_fd_init(void)
{
	struct frame_desc_struct *fd_ptr;
	struct frame_desc_struct *fd_start_ptr;
	struct frame_desc_struct *fd_last_ptr = NULL;
	unsigned long fb_base;
	unsigned long i;

	// TxfdInitialize() in diag code
	// Get Frame descriptor's base address
	// +0x4000000 is for setting this area to non-cacheable area.

	outl((unsigned long)tx_fd | NOCACHE_BIT, BDMATXPTR);
	gtx_ptr =  inl(BDMATXPTR);

	// Get Transmit buffer base address.
	fb_base = (unsigned long)tx_buf | NOCACHE_BIT;

	// Generate linked list.
	fd_start_ptr = fd_ptr = (struct frame_desc_struct *)gtx_ptr;
	fd_last_ptr = NULL;

	for(i = 0; i < TX_FRAME_SIZE; i++) {

		fd_ptr->frame_data_ptr = (unsigned long)(fb_base & CPU_owner);
		fd_ptr->reserved = 0;
		fd_ptr->status_and_frame_lenght = (unsigned long)0x0;

		if(fd_last_ptr != NULL)
			fd_last_ptr->next_frame_desc = (unsigned long)fd_ptr;

		fd_last_ptr = fd_ptr;
		fd_ptr++;

		fb_base += sizeof(struct frame_buf_struct);
	}

	//Make Frame descriptor to ring buffer type.
	fd_last_ptr->next_frame_desc = (unsigned long)fd_start_ptr;

	// RxFDInitialize() in diag code
	// Get Frame descriptor's base address
	outl((unsigned long)rx_fd  | NOCACHE_BIT, BDMARXPTR);
	grx_ptr = inl(BDMARXPTR);

	// Get recieve buffer base address
	fb_base = (unsigned long)rx_buf | NOCACHE_BIT;

	// Generate linked list
	fd_start_ptr = fd_ptr = (struct frame_desc_struct *)grx_ptr;
	fd_last_ptr = NULL;

	for(i = 0; i < RX_FRAME_SIZE; i++) {

		fd_ptr->frame_data_ptr = (unsigned long)(fb_base | BDMA_owner);
		fd_ptr->reserved = 0;
		fd_ptr->status_and_frame_lenght = (unsigned long)0x0;

		if(fd_last_ptr != NULL )
			fd_last_ptr->next_frame_desc = (unsigned long)fd_ptr;

		fd_last_ptr = fd_ptr;
		fd_ptr++;

		fb_base += sizeof(struct frame_buf_struct);
	}   

	// Make Frame descriptor to ring buffer type.
	fd_last_ptr->next_frame_desc = (unsigned long)fd_start_ptr;
}

int s3c4510_eth_init(void)
{	
//	struct eth_cfg eth;
	int i;

//	bios_eth_cfg(&eth);
//	memcpy(s3c4510_eth_addr, eth.address, ETH_ALEN);

	// reset BDMA and MAC
	outl(BRxRS, BDMARXCON);
	outl(BTxRS, BDMATXCON);
	outl(MaxRxFrameSize, BDMARXLSZ);

	outl(Reset, MACON);			//复位MACON, BDMARXCON, BDMATXCON, 设置RxFrameSIZE
	outl(gMACCON, MACON);		

	s3c4510_eth_fd_init();
	for(i = 0; i < 4; i++)
		CAM_Reg(0) = (CAM_Reg(0) << 8) | s3c4510_eth_addr[i];
	for(i = 4; i < 6; i++)
		CAM_Reg(1) = (CAM_Reg(1) << 8) | s3c4510_eth_addr[i];
	CAM_Reg(1) = (CAM_Reg(1) << 16); 		//设置MAC地址

	outl(0x0001, CAMEN);			//ENABLE MAC
	outl(gCAMCON, CAMCON);

	outl(gBDMATXCON, BDMATXCON);
	outl(gMACTXCON, MACTXCON);

	outl(gBDMARXCON, BDMARXCON);
	outl(gMACRXCON, MACRXCON);
	
	return 0;
}

int s3c4510_eth_send(unsigned char *data, unsigned int len)
{
	struct frame_desc_struct *fd_ptr;
	volatile unsigned long *fb_ptr;
	unsigned char *fb_data;
	int i;

	// 1. Get Tx frame descriptor & data pointer
	fd_ptr = (struct frame_desc_struct *)gtx_ptr;
	fb_ptr = (unsigned long *)&fd_ptr->frame_data_ptr;
	fb_data = (unsigned char *)fd_ptr->frame_data_ptr;

	// 2. Check BDMA ownership
	if(*fb_ptr & BDMA_owner)
		return -1;

	// 3. Prepare Tx Frame data to Frame buffer
	memcpy(fb_data, data, len);
	if (len < 60) {
		for (i = len; i < 60; i++)
			fb_data[i] = 0x00;
		len = 60;
	}

	// 4. Set Tx Frame flag & Length Field
	fd_ptr->reserved = (Padding | CRCMode | FrameDataPtrInc | LittleEndian | WA00 | MACTxIntEn);
	fd_ptr->status_and_frame_lenght = (len & 0xFFFF);

	// 5. Change ownership to BDMA
	fd_ptr->frame_data_ptr |= BDMA_owner;

	// 6. Enable MAC and BDMA Tx control register
	outl(gBDMATXCON, BDMATXCON);
	outl(gMACTXCON, MACTXCON);

	// 7. Change the Tx frame descriptor for next use
	gtx_ptr = (unsigned long)(fd_ptr->next_frame_desc);

	return 0;
}

int s3c4510_eth_rcv(unsigned char *data, unsigned int *len)
{
	struct frame_desc_struct *fd_ptr;
	unsigned long rx_status;
	unsigned long bdma_status;
	unsigned char *tmp;

	// 1. Get Rx Frame Descriptor
	fd_ptr = (struct frame_desc_struct *)grx_ptr;
	if (fd_ptr->frame_data_ptr & BDMA_owner)
		return -1;

	rx_status = (fd_ptr->status_and_frame_lenght >> 16) & 0xffff;

	// 2. Get current frame descriptor and status
	bdma_status = inl(BDMASTAT);

	// 3. Clear BDMA status register bit by write 1
	outl(bdma_status | S_BRxRDF, BDMASTAT);

	// 4. If Rx frame is good, then process received frame
	*len = 0;
	if (rx_status & Good) {
		*len = (fd_ptr->status_and_frame_lenght & 0xffff) - 4;
		tmp = (unsigned char *)fd_ptr->frame_data_ptr + 2;

		// 6. Get received frame to memory buffer
		memcpy(data, tmp, *len);
	}

	// 5. Change ownership to BDMA for next use
	fd_ptr->frame_data_ptr |= BDMA_owner;

	// Save Current Status and Frame Length field, and clear
	fd_ptr->status_and_frame_lenght = 0x0;

	// 6. Get Next Frame Descriptor pointer to process
	grx_ptr = (unsigned long)(fd_ptr->next_frame_desc);

	// 7. Check Notowner status
	if (inl(BDMASTAT) & S_BRxNO) {
		outl(S_BRxNO, BDMASTAT);
	}

	if ((inl(MACRXSTAT) & 0x400) == 0x400) {
		outl(gBDMARXCON, BDMARXCON);
		outl(gMACRXCON, MACRXCON);
	}

	return 0;
}

int s3c4510_eth_get_addr(unsigned char *addr)
{
	memcpy(addr, s3c4510_eth_addr, ETH_ALEN);
	return 0;
}
