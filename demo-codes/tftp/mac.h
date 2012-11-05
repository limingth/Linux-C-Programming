#ifndef __MAC_H
#define __MAC_H

#define RX_FRAME_SIZE 64
#define TX_FRAME_SIZE 16

struct frame_desc_struct {
	unsigned long frame_data_ptr;		// [31] Ownership 0=CPU, 1=BDMA
	unsigned long reserved;
	unsigned long status_and_frame_lenght;	// [31:16] Rx Status, [15:0] Frame Length
	unsigned long next_frame_desc;
};

struct frame_buf_struct {
	unsigned char dst[ETH_ALEN];
	unsigned char src[ETH_ALEN];
	unsigned short proto;
	unsigned char data[ETH_DATA_LEN + 22];
};



/* ----------------------------------------- *
 * Definitions of Samsung 4510 MAC registers *
 * ----------------------------------------- */

#define MaxRxFrameSize	(1520)

/* -------------------------------------- *
 * Buffered DMA Transmit Control Register *
 * -------------------------------------- */
#define BTxBRST		(0x0000F) /* [4:0] */
#define BTxSTSKO	(0x00020)
#define BTxCCPIE	(0x00080)
#define BTxNLIE		(0x00100)
#define BTxNOIE		(0x00200)
#define BTxEmpty	(0x00400)
//#define BTxMSL		/* [13:11] */
#define BTxMSL000	(0x00000)
#define BTxMSL001	(0x00800)
#define BTxMSL010	(0x01000)
#define BTxMSL011	(0x01800)
#define BTxMSL100	(0x02000)
#define BTxMSL101	(0x02800)
#define BTxMSL110	(0x03000)
#define BTxMSL111	(0x03800)
#define BTxEn		(0x04000)
#define BTxRS		(0x08000)

/* ------------------------------------- *
 * Buffered DMA Receive Control Register *
 * ------------------------------------- */
#define BRxBRST		(0x0000F) /* [4:0] */
#define BRxSTSKO	(0x00020)
#define BRxMAINC	(0x00040)
#define BRxDIE		(0x00080)
#define BRxNLIE		(0x00100)
#define BRxNOIE		(0x00200)
#define BRxMSOIE	(0x00400)
#define BRxLittle	(0x00800)
//#define BRxWA		/* [13:12] */
#define BRxWA01		(0x01000)
#define BRxWA10		(0x02000)
#define BRxWA11		(0x03000)
#define BRxEn		(0x04000)
#define BRxRS		(0x08000)
#define BRxEmpty	(0x10000)
#define BRxEarly	(0x20000)

/* -------------------- *
 * BDMA Status Register *
 * -------------------- */
#define S_BRxRDF	(0x00001)
#define S_BRxNL		(0x00002)
#define S_BRxNO		(0x00004)
#define S_BRxMSO	(0x00008)
#define S_BRxEmpty	(0x00010)
#define S_BRxSEarly	(0x00020)
#define S_BRxFRF	(0x00080)
#define S_BRxNFR	(0x00080)
#define S_BTxCCP	(0x10000)
#define S_BTxNL		(0x20000)
#define S_BTxNO		(0x40000)
#define S_BTxEmpty	(0x100000)

/* -------------------- *
 * MAC Control Register *
 * -------------------- */
#define HaltReq		(0x00001)
#define HaltImm		(0x00002)
#define Reset		(0x00004)
#define FullDup		(0x00008)
#define MACLoop		(0x00010)
#define MIIOFF		(0x00040)
#define Loop10		(0x00080)
#define MissRoll	(0x00400)
#define MDCOFF		(0x01000)
#define EnMissRoll	(0x02000)
#define Link10		(0x08000)

/* ----------------------------- *
 * MAC Transmit Control Register *
 * ----------------------------- */
#define TxEn		(0x0001)
#define TxHalt		(0x0002)
#define NoPad		(0x0004)
#define NoCRC		(0x0008)
#define FBack		(0x0010)
#define NoDef		(0x0020)
#define SdPause		(0x0040)
#define SQEn		(0x0080)
#define EnUnder		(0x0100)
#define EnDefer		(0x0200)
#define EnNCarr		(0x0400)
#define EnExColl	(0x0800)
#define EnLateColl	(0x1000)
#define EnTxPar		(0x2000)
#define EnComp		(0x4000)

/* ---------------------------- *
 * MAC Receive Control Register *
 * ---------------------------- */
#define RxEn		(0x0001)
#define RxHalt		(0x0002)
#define LongEn		(0x0004)
#define ShortEn		(0x0008)
#define StripCRC	(0x0010)
#define PassCtl		(0x0020)
#define IgnoreCRC	(0x0040)
//#define 		(0x0080)
#define EnAlign		(0x0100)
#define EnCRCErr	(0x0200)
#define EnOver		(0x0400)
#define EnLongErr	(0x0800)
//#define 		(0x1000)
#define EnRxPar		(0x2000)
#define EnGood		(0x4000)

/* -------------------- *
 * CAM Control Register *
 * -------------------- */
#define StationAcc	(0x0001)
#define GroupAcc	(0x0002)
#define BroadAcc	(0x0004)
#define NegCAM		(0x0008)
#define CompEn		(0x0010)

/* Tx & Rx Frame Descriptor Ownership bit[31](O) */ 
#define BDMA_owner	0x80000000 /* BDMA */
#define CPU_owner	0x7fffffff /* CPU  */

/* ------------------------------- *
 * Tx Frame Descriptor Description *
 * ------------------------------- */
#define Padding		(0x00)
#define NoPadding	(0x01)
#define CRCMode		(0x00)
#define NoCRCMode	(0x02)
#define MACTxIntEn	(0x04)
#define MACTxIntDis	(0x00)
#define LittleEndian	(0x08)
#define BigEndian	(0x00)
#define FrameDataPtrInc	(0x10)
#define FrameDataPtrDec	(0x00)
#define WA00		(0x00)
#define WA01		(0x20)
#define WA10		(0x40)
#define WA11		(0x60)

/* --------- *
 * Tx Status *
 * --------- */
#define TxCollCntMask	(0x000F)
#define ExColl		(0x0010)
#define TxDefer		(0x0020)
#define Paused		(0x0040)
#define IntTx		(0x0080)
#define Under		(0x0100)
#define Defer		(0x0200)
#define NCarr		(0x0400)
#define SQErr		(0x0800)
#define LateColl	(0x1000)
#define TxPar		(0x2000)
#define Comp		(0x4000)
#define TxHalted	(0x8000)

/* --------- *
 * Rx Status *
 * --------- */
#define OvMax		(0x0004)
#define CtlRcv		(0x0020)
#define IntRx		(0x0040)
#define Rx10stat	(0x0080)
#define AlignErr	(0x0100)
#define CRCErr		(0x0200)
#define Overflow	(0x0400)
#define LongErr		(0x0800)
#define RxPar		(0x2000)
#define Good		(0x4000)
#define RxHalted	(0x8000)

/* ------------- *
 * MII Registers *
 * ------------- */

#define PHYHWADDR       0x3E0
#define MiiBusy		(1<<11)
#define PHYREGWRITE	(1<<10)

enum {
	gMACCON = FullDup,
	gMACTXCON = EnComp | TxEn,
	gMACRXCON = RxEn,
	gBDMATXCON = BTxBRST | BTxMSL110 | BTxSTSKO | BTxEn,
	gBDMARXCON = BRxDIE | BRxEn | BRxLittle | BRxMAINC | BRxBRST | BRxNLIE | BRxNOIE | BRxSTSKO | BRxWA10,
	gCAMCON = CompEn | BroadAcc
};

int s3c4510_eth_init(void);
int s3c4510_eth_send(unsigned char *data, unsigned int len);
int s3c4510_eth_rcv(unsigned char *data, unsigned int *len);
int s3c4510_eth_get_addr(unsigned char *addr);

#endif /* __MAC_H */
