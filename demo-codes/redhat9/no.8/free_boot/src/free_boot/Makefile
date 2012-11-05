CC = arm-elf-gcc
LD = arm-elf-ld
OBJCOPY = arm-elf-objcopy
CFLAGS = -O0 -Wall

all: bios bios.bin
	ls -l bios.bin
	
bios:main.c init.S uart.c led_api.c led_driver.c shell.c my_printf.c my_string.c flash_39vf160.c xmodem.c
	$(CC) $(CFLAGS) -g -static -c main.c 
	$(CC) $(CFLAGS) -g -static -c shell.c 
	$(CC) $(CFLAGS) -g -static -c init.S
	$(CC) $(CFLAGS) -g -static -c command.c
	$(CC) $(CFLAGS) -g -static -c uart.c
	$(CC) $(CFLAGS) -g -static -c led_api.c
	$(CC) $(CFLAGS) -g -static -c led_driver.c
	$(CC) $(CFLAGS) -g -static -c my_printf.c
	$(CC) $(CFLAGS) -g -static -c my_string.c
	$(CC) $(CFLAGS) -g -static -c flash_39vf160.c
	$(CC) $(CFLAGS) -g -static -c xmodem.c
	#$(LD) -N -p -X -T ld-script.ld main.o shell.o init.o command.o led_api.o led_driver.o uart.o my_printf.o my_string.o -o bios -lc -L/usr/local/xscale/3.3.3/lib/ -lgcc -L/usr/local/xscale/3.3.3/arm-linux/lib/gcc-lib/arm-linux/3.3.3/
	$(LD) -N -p -X -T ld-script.ld main.o shell.o init.o command.o led_api.o led_driver.o uart.o my_printf.o \
		my_string.o flash_39vf160.o xmodem.o -o bios 
	arm-elf-objdump -D bios>a.list

#bios.bin: bios
#	$(OBJCOPY) -O binary \
		--only-section=.init \
		--only-section=.text \
		--only-section=.rodata \
		--only-section=.data\
		--only-section=.bss bios bios.bin
bios.bin: bios
	$(OBJCOPY) -O binary \
		--only-section=.init \
		--only-section=.text \
		--only-section=.rodata bios bios_ro.bin 
	$(OBJCOPY) -O binary \
		--only-section=.data\
		--only-section=.bss bios bios_rw.bin
	cat bios_ro.bin>bios.bin
	cat bios_rw.bin>>bios.bin
	#sudo cp bios.bin /home/ftp/incoming
clean:
	rm *.o bios bios.bin
#	--only-section=.data \
