all:
	gcc -c main.c
	gcc -c add.c
	gcc -c sub.c
	gcc -o hello.elf main.o add.o sub.o

ar:
	ar -rv libtest.a add.o sub.o
	gcc -o test main.c -ltest

ar2:
	gcc -o test main.c -ltest -L.

nm:
	nm add.o
	nm sub.o
	nm main.o
	nm hello

objdump:
	objdump -d add.o > add.lst
	objdump -d sub.o > sub.lst
	objdump -d main.o > main.lst
	
objdump2:
	objdump -S -j .text hello.elf > all.lst
	objdump -S -j .rodata hello.elf >> all.lst
	objdump -S -j .data hello.elf >> all.lst

objcopy:
	objcopy -O binary --only-section=.text hello.elf text.bin
	objcopy -O binary --only-section=.data hello.elf data.bin
	objcopy -O binary --only-section=.rodata hello.elf rodata.bin

readelf:
	readelf -a hello.elf

strip:
	strip hello.elf -o hello.strip

clean:
	rm -rf *.o
	rm -rf *.lst 


