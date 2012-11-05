
simple:
	gcc -c -o main.o main.c 
	gcc -c -o add.o add.c 
	gcc -o main.elf main.o add.o 

all:
	objdump -S -j .text main.elf > m.lst
	objdump -S -j .rodata main.elf >> m.lst
	objdump -S -j .data main.elf >> m.lst

else:
	nm add.o 
	nm max.o 
	nm hello.o
	objdump -f hello 
	objdump -d hello.o 
	objdump -d add.o
	objdump -d max.o
	objdump -d hello 
