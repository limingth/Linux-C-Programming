
simple:
	gcc -o main.elf main.c 
	gcc -S -o main.s main.c 

t:
	./main.elf

all:
	objdump -S -j .text main.elf > m.lst
	objdump -S -j .rodata main.elf >> m.lst
	objdump -S -j .data main.elf >> m.lst

