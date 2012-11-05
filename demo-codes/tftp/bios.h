#ifndef __BIOS_H
#define __BIOS_H

#include "config.h"

#define MAX_PARTITION_NUM                  8
#define PARTITION_FLAGS_READWRITE          0x0001
#define PARTITION_FLAGS_ROOT               0x4000
#define PARTITION_FLAGS_ACTIVE             0x8000

#define DEVICE_FLAGS_ENABLE                0x80000000

#define BIOSCALL_INIT                      0x00000000
#define BIOSCALL_REBOOT                    0x00000001
#define BIOSCALL_GET_SYSCLOCK              0x00000002
#define BIOSCALL_GET_EXTCLOCK              0x00000003
#define BIOSCALL_GET_ROMBASE               0x00000004
#define BIOSCALL_GET_ROMSIZE               0x00000005
#define BIOSCALL_GET_DRAMBASE              0x00000006
#define BIOSCALL_GET_DRAMSIZE              0x00000007
#define BIOSCALL_GET_BIOSOFFSET            0x00000008
#define BIOSCALL_GET_BIOSSIZE              0x00000009
#define BIOSCALL_GET_SYSTEMTABLEOFFSET     0x0000000a
#define BIOSCALL_GET_SYSTEMTABLESIZE       0x0000000b
#define BIOSCALL_GET_PARTITIONTABLEOFFSET  0x0000000c
#define BIOSCALL_GET_PARTITIONTABLESIZE    0x0000000d
#define BIOSCALL_FLASH_ERASE               0x0000000e
#define BIOSCALL_FLASH_READ                0x0000000f
#define BIOSCALL_FLASH_WRITE               0x00000010
#define BIOSCALL_GET_UART0CFG              0x00000011
#define BIOSCALL_GET_UART1CFG              0x00000012
#define BIOSCALL_GET_ETHCFG                0x00000013
#define BIOSCALL_GET_NE2000CFG             0x00000014
#define BIOSCALL_GET_UART16550CFG          0x00000015
#define BIOSCALL_GET_PC97338CFG            0x00000016
#define BIOSCALL_GET_STARTUPMODE           0x00000017
#define BIOSCALL_GET_TFTPIPADDR            0x00000018
#define BIOSCALL_GET_VENDORID              0x00000019
#define BIOSCALL_GET_DEVICEID              0x0000001a
#define BIOSCALL_GET_SUBVENDORID           0x0000001b
#define BIOSCALL_GET_SUBDEVICEID           0x0000001c
#define BIOSCALL_GET_REV                   0x0000001d


#define BOOT_LOAD_FIRMWARE                 0x00000000
#define BOOT_LOAD_PROGRAM                  0x00000001
#define BOOT_BIOS_SETUP                    0x00000002
#define BOOT_FDISK_UTILITY                 0x00000003
#define BOOT_UPDATE_BIOS                   0x00000004
#define BOOT_UPDATE_SYSPARAMETERS          0x00000005
#define BOOT_UPDATE_PARTITIONTABLE         0x00000006
#define BOOT_UPDATE_PARTITION              0x00000007
#define BOOT_UPDATE_FIRMWARE               0x00000008
#define BOOT_MENU                          0x00000009

#define FIRMWARE_BIOS                      0x0001
#define FIRMWARE_SYSPARAMETERS             0x0002
#define FIRMWARE_PARTITIONTABLE            0x0003
#define FIRMWARE_PARTITION                 0x0004

#define FDISK_CREATE_PARTITION             0x00000000
#define FDISK_DELETE_PARTITION             0x00000001
#define FDISK_DISPLAY_PARTITION            0x00000002

#define SETUP_ROM                          0x00000000
#define SETUP_DRAM                         0x00000001
#define SETUP_BOOT_MODE                    0x00000002
#define SETUP_ETH                          0x00000003
#define SETUP_NE2000                       0x00000004

typedef int (BIOSCALL)(unsigned long id, unsigned long arg);


struct partition_struct {
	unsigned short flags;
	unsigned short type;
	long offset;
	long size;
	long param;
};

struct partition_table_struct {
	struct partition_struct partition[MAX_PARTITION_NUM];
};


struct sys_regs_struct {

	unsigned long extdbwth;
	unsigned long romcon[6];
	unsigned long dramcon[4];
	unsigned long refextcon;
};

struct sys_dram_cfg {
	unsigned long size;
	unsigned long width;
	unsigned long flags;
};

struct sys_rom_cfg {
	unsigned long size;
	unsigned long width;
	unsigned long flags;
};

struct sys_ext_cfg {
	unsigned long width;
	unsigned long flags;
};

struct sys_iop_cfg {
	unsigned long iopmod;
	unsigned long iopcon;
	unsigned long iopdata;
};

struct sys_uart_cfg {
	unsigned long flags;
	unsigned long port;
	unsigned char reserve[2];
	unsigned char dma_rx;
	unsigned char dma_tx;
	unsigned long mode;
};

struct sys_eth_cfg {
	unsigned long flags;
	unsigned char address[6];
};

struct sys_ne2000_cfg {
	unsigned long flags;
	unsigned long bank;
	unsigned char address[6];
};

struct sys_uart16550_cfg {
	unsigned long flags;
	unsigned long bank;
	unsigned long clock;
};

struct sys_pc97338_cfg {
	unsigned long flags;
	unsigned long bank;
};

struct system_table_struct {

	unsigned short vendor_id;
	unsigned short device_id;

	unsigned short sub_vendor_id;
	unsigned short sub_device_id;

	unsigned long rev;

	unsigned long bios_size;

	unsigned long system_table_size;

	unsigned long partition_table_offset;
	unsigned long partition_table_size;

	unsigned long sys_reg_base;
	unsigned long sys_clock;
	unsigned long ext_clock;

	struct sys_rom_cfg rom_table[6];

	struct sys_dram_cfg dram_table[4];

	unsigned long ext_base;
	struct sys_ext_cfg ext_table[4];

	struct sys_iop_cfg iop;
	struct sys_uart_cfg uart[2];
	struct sys_eth_cfg eth;

	struct sys_ne2000_cfg ne2000;
	struct sys_uart16550_cfg uart16550;
	struct sys_pc97338_cfg pc97338;

	unsigned long startup_mode;
	unsigned long tftp_ipaddr;

};

struct uart_cfg {
	unsigned long flags;
	unsigned long base;
	unsigned char irq_rx;
	unsigned char irq_tx;
	unsigned char dma_rx;
	unsigned char dma_tx;
	unsigned long mode;
};

struct eth_cfg {
	unsigned long flags;
	unsigned long base;
	unsigned char address[6];
};

struct ne2000_cfg {
	unsigned long flags;
	unsigned long base;
	unsigned char address[6];
};

struct uart16550_cfg {
	unsigned long flags;
	unsigned long base;
	unsigned long clock;
};

struct pc97338_cfg {
	unsigned long flags;
	unsigned long base;
};

struct flash_erase_struct {
	unsigned long addr;
	unsigned long size;
};

struct flash_read_struct {
	unsigned long from;
	unsigned long len;
	unsigned long retlen;
	unsigned char *buf;
};

struct flash_write_struct {
	unsigned long to;
	unsigned long len;
	unsigned long retlen;
	unsigned char *buf;
};

struct biosapi_init_struct {
	unsigned long rom_base;
	unsigned long dram_base;
	unsigned long system_table_offset;
};

struct config_table_struct {

	unsigned short vendor_id;
	unsigned short device_id;

	unsigned short sub_vendor_id;
	unsigned short sub_device_id;

	unsigned long rev;

	unsigned long bios_offset;
	unsigned long bios_size;

	unsigned long system_table_offset;
	unsigned long system_table_size;

	unsigned long partition_table_offset;
	unsigned long partition_table_size;

	unsigned long sys_clock;
	unsigned long ext_clock;

	unsigned long rom_base;
	unsigned long rom_size;

	unsigned long dram_base;
	unsigned long dram_size;

	struct uart_cfg uart[2];
	struct eth_cfg eth;
	struct ne2000_cfg ne2000;
	struct uart16550_cfg uart16550;
	struct pc97338_cfg pc97338;

	unsigned long startup_mode;
	unsigned long tftp_ipaddr;

};

__packed struct firmware_hdr {
	unsigned short vendor_id;
	unsigned short device_id;

	unsigned short sub_vendor_id;
	unsigned short sub_device_id;

	unsigned long rev;

	unsigned long offset;
};//__attribute__ ((packed));

__packed struct firmware_section_hdr {
	unsigned short flags;
	unsigned short type;
	long offset;
	long size;
	long param;
};//__attribute__ ((packed));

#endif  /* __BIOS_H */
