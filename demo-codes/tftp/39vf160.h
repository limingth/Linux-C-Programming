unsigned int ReadSWPID(void);
void ReadCFIInfo(unsigned short *DataPtr);
void ChipErase(void);
void SectorErase(unsigned int sector);
void FlashProg(unsigned int ProgStart, unsigned short *DataPtr, unsigned int Size);
void FlashRead(unsigned int ReadStart, unsigned short *DataPtr, unsigned int Size);
int SectorProg(unsigned int begin, unsigned short *data, unsigned int size);