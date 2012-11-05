#include "console.h"
#include "DataType.h"

#define	ROM_BASE	(0x1000000|0x4000000)
#define	CMD_ADDR0	*((volatile U16 *)(0x5555*2+ROM_BASE))
#define	CMD_ADDR1	*((volatile U16 *)(0x2aaa*2+ROM_BASE))

static U8 state = 0;

static void CFIQueryExit(void)
{
	CMD_ADDR0 = 0xaaaa;
	CMD_ADDR1 = 0x5555;
	CMD_ADDR0 = 0xf0f0;
	state &= 0xfc;	
}

static void SWPIDExit(void)
{
	CMD_ADDR0 = 0xf0f0;
	state &= 0xfc;
}

static void CFIQueryEntry(void)
{
	if(state&1)
	{
		if(state&2)
			SWPIDExit();
		else
			return;
	}
	
	CMD_ADDR0 = 0xaaaa;
	CMD_ADDR1 = 0x5555;
	CMD_ADDR0 = 0x9898;
	state |= 1;	
}

static void SWPIDEntry(void)
{
	if(state&1)
	{
		if(state&2)
			return;
		else
			CFIQueryExit();
	}

	CMD_ADDR0 = 0xaaaa;
	CMD_ADDR1 = 0x5555;
	CMD_ADDR0 = 0x9090;
	state |= 3;
}

U32 ReadSWPID(void)
{
	U32 i;
	
	SWPIDEntry();
	i  = *(U16 *)(0+ROM_BASE);
	i |= (*(U16 *)(2+ROM_BASE))<<16;
	SWPIDExit();
	return i;	
}

void ReadCFIInfo(U16 *DataPtr)
{
	U16 i;
	
	CFIQueryEntry();
	for(i = 0x10; i<0x35; DataPtr++, i++)
		*DataPtr = *(U16 *)(i*2+ROM_BASE);	
	CFIQueryExit();
}

void ChipErase(void)
{
	if(state&1)
	{
		if(state&2)
			SWPIDExit();
		else
			CFIQueryExit();						
	}
	
	CMD_ADDR0 = 0xaaaa;
	CMD_ADDR1 = 0x5555;
	CMD_ADDR0 = 0x8080;
	CMD_ADDR0 = 0xaaaa;
	CMD_ADDR1 = 0x5555;
	CMD_ADDR0 = 0x1010;

	while(1)
	{
		U16 i;
		i = *((volatile U16 *)0x6666)&0x40;
		if(i!=*((volatile U16 *)0x6666)&0x40)	//D6 == D6
			continue;
		if(*((volatile U16 *)0x8888)&0x80)	
			break;						//D7 == 1
	}		
}

void SectorErase(U32 sector)
{
	if(state&1)
	{
		if(state&2)
			SWPIDExit();
		else
			CFIQueryExit();						
	}
	
	sector += ROM_BASE;	
	
	CMD_ADDR0 = 0xaaaa;
	CMD_ADDR1 = 0x5555;
	CMD_ADDR0 = 0x8080;
	CMD_ADDR0 = 0xaaaa;
	CMD_ADDR1 = 0x5555;
	*(volatile U16 *)sector = 0x3030;
	
	while(1)
	{
		U16 i;
		i = *((volatile U16 *)sector)&0x40;
		if(i!=*((volatile U16 *)sector)&0x40)	//D6 == D6
			continue;
		if(*((volatile U16 *)sector)&0x80)	
			break;								//D7 == 1
	}
	
	printf("Erase sector 0x%x	ok\n", sector-ROM_BASE);				

}

void FlashProg(U32 ProgStart, U16 *DataPtr, U32 WordCnt)
{
	U16 i, j;	
	
	ProgStart += ROM_BASE;
	
	for( ; WordCnt; ProgStart+=2, DataPtr++, WordCnt--)
	{	
		j = *DataPtr;
		CMD_ADDR0 = 0xaaaa;
		CMD_ADDR1 = 0x5555;
		CMD_ADDR0 = 0xa0a0;
		*(volatile U16 *)ProgStart = j;	
		
		while(1)
		{
			i = *(volatile U16 *)ProgStart&0x40;
			if(i!=*(volatile U16 *)ProgStart&0x40)		//D6 == D6
				continue;
			if((*(volatile U16 *)ProgStart&0x80)==(j&0x80))	
				break;					//D7 == D7
		}
	}
	
}

void FlashRead(unsigned int ReadStart, unsigned short *DataPtr, unsigned int Size)
{
	int i;
	
	ReadStart += ROM_BASE;
	
	for(i=0; i<Size/2; i++)
		*(DataPtr+i) = *((unsigned short *)ReadStart+i);	
	
}

int SectorProg(U32 begin, U16 *data, U32 size)
{		
	U32 tmp = 0x1000-(begin&0xfff);
	
	if(tmp>size)
		tmp = size;
	
	for(; size;)
	{	
		SectorErase(begin&0xfffff000);	//4K Bytes boudary		
		FlashProg(begin, data, tmp/2);
		puts("Program ok\n");
		
		size  -= tmp;
		begin += tmp;
		data  += tmp/2;
		tmp = (size>0x1000)?0x1000:size;				
	}
	return 0;			
}