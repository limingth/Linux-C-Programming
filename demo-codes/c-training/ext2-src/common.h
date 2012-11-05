#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdlib.h>

#define BLKSZ_1K 1024
#define ISZ 128

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void err_sys(const char *str);
extern void err_usr(const char *str);

extern inline u32 blk_to_addr(void *fs, u16 blksz, u32 blkno);
extern inline u32* root_index(void *fs, u16 blksz);

#endif
