all:
	arm-elf-gcc -DEMBED -elf2flt main.c led_drv.c led_api.c -o ledblink
	gcc -O0 -g -Wall main.c led_drv.c led_api.c -o demo

clean:
	rm *.gdb
	rm *.o
