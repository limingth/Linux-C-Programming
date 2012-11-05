#ifndef __BIOSCALL_H
#define __BIOSCALL_H

#include "bios.h"

int bios_call(unsigned long id, unsigned long arg);
int bios_reboot(void);
unsigned short bios_vendor_id(void);
unsigned short bios_device_id(void);
unsigned short bios_sub_vendor_id(void);
unsigned short bios_sub_device_id(void);
unsigned long bios_rev(void);
unsigned long bios_sys_clock(void);
unsigned long bios_ext_clock(void);
unsigned long bios_dram_base(void);
unsigned long bios_dram_size(void);
unsigned long bios_rom_base(void);
unsigned long bios_rom_size(void);
unsigned long bios_bios_offset(void);
unsigned long bios_bios_size(void);
unsigned long bios_system_table_offset(void);
unsigned long bios_system_table_size(void);
unsigned long bios_partition_table_offset(void);
unsigned long bios_partition_table_size(void);
unsigned long bios_startup_mode(void);
unsigned long bios_tftp_ipaddr(void);
int bios_flash_erase(unsigned long adr, unsigned long size);
int bios_flash_read(unsigned long from,
	unsigned long len, unsigned long *retlen, unsigned char *buf);
int bios_flash_write(unsigned long to,
	unsigned long len, unsigned long *retlen, unsigned char *buf);
int bios_uart0_cfg(struct uart_cfg *cfg);
int bios_uart1_cfg(struct uart_cfg *cfg);
int bios_eth_cfg(struct eth_cfg *cfg);
int bios_ne2000_cfg(struct ne2000_cfg *cfg);

int bios_system_table(struct system_table_struct *system_table);
int bios_partition_table(struct partition_table_struct *partition_table);

#endif  /* __BIOSCALL_H */
