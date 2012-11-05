
all: step1 step2 step3 
	gcc -o main main.c add.c sub.c

step1:
	gcc -S -o main.s main.c
	gcc -S -o add.s add.c
	gcc -S -o sub.s sub.c

step2:
	gcc -c -o main.o main.c
	gcc -c -o add.o add.c
	gcc -c -o sub.o sub.c

step3:
	gcc -o main.elf main.o add.o sub.o 

step4:
	objdump -d add.o > add.lst
	objdump -d sub.o > sub.lst
	objdump -d main.o > main.lst

	objdump -S -j .text main.elf > m.lst
	objdump -S -j .rodata main.elf >> m.lst
	objdump -S -j .data main.elf >> m.lst

step5:
	objdump -t main.o > main-symble.lst

step6:
	objcopy -O binary --only-section=.text main.elf text.bin 
	objcopy -O binary --only-section=.data main.elf data.bin 

step7:
	nm main.elf
	strip main.elf
	nm main.elf





