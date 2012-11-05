
simple:
	gcc -g -c -o hello.o hello.c 
	gcc -g -o hello hello.c 

t:
	./hello

t1:
	objdump -S -j .text hello

t2:
	objdump -S -j .data hello

t3:
	objdump -S -j .rodata hello

all:
	objdump -S -j .text hello > m.lst
	objdump -S -j .rodata hello >> m.lst
	objdump -S -j .data hello >> m.lst
	objdump -S -j .bss hello >> m.lst

	
