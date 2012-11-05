all:
	arm-elf-gcc -O0 -DEMBED -elf2flt main.c led.c -o ledblink
	gcc -O0 main.c led.c -o demo

clean:
	rm *.gdb
	rm *.o
