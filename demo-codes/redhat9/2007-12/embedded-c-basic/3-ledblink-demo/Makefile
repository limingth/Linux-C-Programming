all:
	arm-elf-gcc -DEMBED -elf2flt main.c led.c -o ledblink
	gcc main.c led.c -o demo

clean:
	rm *.gdb
	rm *.o
