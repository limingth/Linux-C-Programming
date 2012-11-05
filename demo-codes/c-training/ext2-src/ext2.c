#include "common.h"

inline u32 blk_to_addr(void *fs, u16 blksz, u32 blkno)
{
	return (u32)fs + blksz * blkno;
}

inline u32 super_base(void *fs)
{
	return (u32)fs + BLKSZ_1K;
}

inline u32 grp0_base(void *fs, u16 blksz)
{
	return blk_to_addr(fs, blksz, (*(u32 *)(super_base(fs) + 20) + 1));
}

inline u32 grp0_itb_base(void *fs, u16 blksz)
{
	return blk_to_addr(fs, blksz, *((u32 *)(grp0_base(fs, blksz) + 8)));
}

inline u32 root_inode_base(void *fs, u16 blksz)
{
	return grp0_itb_base(fs, blksz) + ISZ;
}

inline u32* root_index(void *fs, u16 blksz)
{
	return (u32 *)(root_inode_base(fs, blksz) + 40);
}
